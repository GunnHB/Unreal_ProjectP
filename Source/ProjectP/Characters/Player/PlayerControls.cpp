// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControls.h"

#include "../../InputData/PlayerInputData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerAnimInstance.h"

// Sets default values
APlayerControls::APlayerControls()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING_ARM"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	InitAssets();
	InitComponentsValue();
}

// Called when the game starts or when spawned
void APlayerControls::BeginPlay()
{
	Super::BeginPlay();
	
	mAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	MappingContext();
}

// Called every frame
void APlayerControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerControls::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindInputActions(PlayerInputComponent);
}

void APlayerControls::InitAssets()
{
	// mesh
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh>
			asset(TEXT("/Script/Engine.SkeletalMesh'/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Quinn_Weapon.SKM_Quinn_Weapon'"));

		if (asset.Succeeded())
			GetMesh()->SetSkeletalMesh(asset.Object);
	}

	// animinstance
	{
		// animation blueprint
		static ConstructorHelpers::FClassFinder<UAnimInstance>
			asset(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Animations/ABP_PlayerControls.ABP_PlayerControls_C'"));

		if (asset.Succeeded())
			GetMesh()->SetAnimInstanceClass(asset.Class);
	}
}

void APlayerControls::InitComponentsValue()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(89.f);
	GetCapsuleComponent()->SetCapsuleRadius(25.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -92.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	mSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

	mInputVector = FVector::ZeroVector;
	mCamRotator = FRotator::ZeroRotator;

	mSpringArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mSpringArm);

	mSpringArm->TargetArmLength = 300.f;
	mSpringArm->bInheritYaw = false;

	// ��Ʈ�ѷ��� ȸ���� ������ ���� �ʵ���
	bUseControllerRotationYaw = false;

	// �̵� �ӵ� ����
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetCharacterMovement());

	if (movement != nullptr)
		movement->MaxWalkSpeed = 500.f;
}

void APlayerControls::BindInputActions(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	const UPlayerInputData* inputData = GetDefault<UPlayerInputData>();

	if (InputComponent == nullptr || inputData == nullptr)
		return;

	inputComponent->BindAction(inputData->mInputToMovement, ETriggerEvent::Triggered, this, &APlayerControls::MovementAction);
	inputComponent->BindAction(inputData->mInputToMovement, ETriggerEvent::Completed, this, &APlayerControls::MovementStopAction);
	inputComponent->BindAction(inputData->mInputToCameraMovement, ETriggerEvent::Triggered, this, &APlayerControls::CameraMovementAction);
	inputComponent->BindAction(inputData->mInputToJump, ETriggerEvent::Started, this, &APlayerControls::JumpAction);
	inputComponent->BindAction(inputData->mInputToAttack, ETriggerEvent::Started, this, &APlayerControls::AttackAction);
	inputComponent->BindAction(inputData->mInputToSprint, ETriggerEvent::Started, this, &APlayerControls::SprintAction);
	inputComponent->BindAction(inputData->mInputToFocus, ETriggerEvent::Triggered, this, &APlayerControls::FocusAction);
}

void APlayerControls::MappingContext()
{
	APlayerController* player = Cast<APlayerController>(GetController());

	if (player == nullptr)
		return;

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player->GetLocalPlayer());
	const UPlayerInputData* inputData = GetDefault<UPlayerInputData>();

	subsystem->AddMappingContext(inputData->mContext, 0);
}

#pragma region Actions
void APlayerControls::MovementAction(const FInputActionValue& value)
{
	mInputVector = value.Get<FVector>();

	AdjustActorRotation();

	AddMovementInput(GetActorForwardVector());
}

void APlayerControls::MovementStopAction(const FInputActionValue& value)
{
	mInputVector = FVector::ZeroVector;
}

void APlayerControls::CameraMovementAction(const FInputActionValue& value)
{
	FVector axis = value.Get<FVector>();

	float pitchDelta = axis.Y * 90.f * GetWorld()->GetDeltaSeconds();
	float yawDelta = axis.X * 90.f * GetWorld()->GetDeltaSeconds();

	mCamRotator.Pitch += pitchDelta;
	mCamRotator.Yaw += yawDelta;

	AdjustCameraRotation();

	mSpringArm->SetRelativeRotation(mCamRotator);
}

void APlayerControls::JumpAction(const FInputActionValue& value)
{
	Jump();
}

void APlayerControls::AttackAction(const FInputActionValue& value)
{
	//NormalAttack();
}

void APlayerControls::SprintAction(const FInputActionValue& value)
{
	
}

void APlayerControls::FocusAction(const FInputActionValue& value)
{
	bFocus = !bFocus;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("focus = %d"), bFocus));
}
#pragma endregion

void APlayerControls::AdjustCameraRotation()
{
	// yaw
	if (mCamRotator.Yaw > 180.f)
		mCamRotator.Yaw = mCamRotator.Yaw - 360.f;
	else if (mCamRotator.Yaw < -180.f)
		mCamRotator.Yaw = 360.f + mCamRotator.Yaw;

	// pitch
	if (mCamRotator.Pitch < -60.f)
		mCamRotator.Pitch = -60.f;
	else if (mCamRotator.Pitch > 60.f)
		mCamRotator.Pitch = 60.f;
}
void APlayerControls::AdjustActorRotation()
{
	FVector direction = mInputVector.GetSafeNormal();

	float targetAngle = FMath::Atan2(direction.X, direction.Y) * FMathf::RadToDeg + mSpringArm->GetRelativeRotation().Yaw;

	// targetAngle ����
	if (targetAngle < -180.f)
		targetAngle = 360 + targetAngle;
	else if (targetAngle > 180.f)
		targetAngle = targetAngle - 360.f;

	FRotator targetRotation = FRotator(0.f, targetAngle, 0.f);
	// ȸ�� ���� // interpspeed ���� Ŭ���� ������ ȸ��
	FRotator rotation = FMath::RInterpTo(GetActorRotation(), targetRotation, GetWorld()->GetDeltaSeconds(), 10.f);

	// ���������� ȸ��
	SetActorRotation(rotation);
}

void APlayerControls::NormalAttack()
{
	mAnimInstance->PlayAttackMontage();
}