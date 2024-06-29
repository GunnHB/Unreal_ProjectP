// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControls.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../../InputData/PlayerInputData.h"
#include "PlayerAnimInstance_SS.h"

// Sets default values
APlayerControls::APlayerControls()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING_ARM"));

	mSpringArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mSpringArm);
}

// Called when the game starts or when spawned
void APlayerControls::BeginPlay()
{
	Super::BeginPlay();

	mCamRotator = mSpringArm->GetRelativeRotation();

	mAnimInstance = Cast<UPlayerAnimInstance_SS>(GetMesh()->GetAnimInstance());

	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (playerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
		
		const UPlayerInputData* inputData = GetDefault<UPlayerInputData>();

		subsystem->AddMappingContext(inputData->mContext, 0);
	}
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

	UEnhancedInputComponent* inputCompo = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (inputCompo == nullptr)
		return;

	const UPlayerInputData* inputData = GetDefault<UPlayerInputData>();

	inputCompo->BindAction(inputData->mInputToMovement, ETriggerEvent::Triggered, this, &APlayerControls::MovementAction);
	inputCompo->BindAction(inputData->mInputToMovement, ETriggerEvent::Completed, this, &APlayerControls::MovementStopAction);
	inputCompo->BindAction(inputData->mInputToCameraMovement, ETriggerEvent::Triggered, this, &APlayerControls::CameraMovementAction);
	inputCompo->BindAction(inputData->mInputToAttack, ETriggerEvent::Started, this, &APlayerControls::AttackAction);
	inputCompo->BindAction(inputData->mInputToJump, ETriggerEvent::Started, this, &APlayerControls::JumpAction);
}

void APlayerControls::InitAssets()
{
}

void APlayerControls::InitComponentValues()
{
}

void APlayerControls::MovementAction(const FInputActionValue& value)
{
	mInputAxis = value.Get<FVector>();

	AdjustActorRotation();

	AddMovementInput(GetActorForwardVector());
}

void APlayerControls::MovementStopAction(const FInputActionValue& value)
{
	mInputAxis = FVector::ZeroVector;
}

void APlayerControls::CameraMovementAction(const FInputActionValue& value)
{
	FVector axis = value.Get<FVector>();

	float pitchDelta = axis.Y * 90.f * GetWorld()->GetDeltaSeconds();
	float yawDelta = axis.X * 90.f * GetWorld()->GetDeltaSeconds();

	mCamRotator.Pitch += pitchDelta;
	mCamRotator.Yaw += yawDelta;

	AdjustCamRotation(mCamRotator);

	mSpringArm->SetRelativeRotation(mCamRotator);
}

void APlayerControls::AttackAction(const FInputActionValue& value)
{
	NormalAttack();
}

void APlayerControls::NormalAttack()
{
}

void APlayerControls::AttackEnable()
{
}

void APlayerControls::AttackDisable()
{
	//mAnimInstance->ResetDatas();
}

void APlayerControls::JumpAction(const FInputActionValue& value)
{
	if (CanJump())
	{
		Jump();
		mAnimInstance->OnJump();
	}
}