// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControls.h"

#include "../../InputData/PlayerInputData.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerAnimInstance.h"

APlayerControls::APlayerControls()
{
	mArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING_ARM"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	mArm->SetupAttachment(mCapsule);
	mCamera->SetupAttachment(mArm);

	InitAssets();
	InitCompoValues();
}

void APlayerControls::BeginPlay()
{
	Super::BeginPlay();

	mCamRotator = mArm->GetRelativeRotation();

	mAnimInstance = Cast<UPlayerAnimInstance>(mSkeletalMesh->GetAnimInstance());

	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (playerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

		// ����� inputdata�� ����Ʈ��
		// CDO ������
		// �⺻ �ν��Ͻ��� �̸� �������� �����ؼ� ����ϱ� ����
		const UPlayerInputData* inputData = GetDefault<UPlayerInputData>();

		subsystem->AddMappingContext(inputData->mContext, 0);	
	}
}

void APlayerControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerControls::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ������ �Է��� EnhancedinputComponent�� ĳ����
	UEnhancedInputComponent* inputCompo = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (inputCompo == nullptr)
		return;

	// CDO ������
	const UPlayerInputData* inputData = GetDefault<UPlayerInputData>();

	inputCompo->BindAction(inputData->mMovementAction, ETriggerEvent::Triggered, this, &APlayerControls::MovementAction);
	inputCompo->BindAction(inputData->mCameraMovementAction, ETriggerEvent::Triggered, this, &APlayerControls::CameraMovementAction);
}

void APlayerControls::InitAssets()
{
	// mesh
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh>
			asset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonCrunch/Characters/Heroes/Crunch/Skins/Tier_3/BlackSite/Meshes/Crunch_Black_Site.Crunch_Black_Site'"));

		if (asset.Succeeded())
			mSkeletalMesh->SetSkeletalMesh(asset.Object);
	}

	// animInstance
	{
		static ConstructorHelpers::FClassFinder<UAnimInstance>
			asset(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Animations/BP_PlayerControls_Crunch.BP_PlayerControls_Crunch_C'"));

		if (asset.Succeeded())
			mSkeletalMesh->SetAnimInstanceClass(asset.Class);
	}
}

void APlayerControls::InitCompoValues()
{
	// capsule
	mCapsule->SetCapsuleHalfHeight(130.f);
	mCapsule->SetCapsuleRadius(70.f);

	// mesh
	mSkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, -130.f));
	mSkeletalMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// spring arm
	mArm->TargetArmLength = 500.f;
	mArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

	// movement speed
	SetMovementSpeed(500.f);

	// camera rotator
	mCamRotator = mArm->GetRelativeRotation();
}

void APlayerControls::MovementAction(const FInputActionValue& value)
{
	FVector axis = value.Get<FVector>();

	FVector vertical = GetActorForwardVector() * axis.Y;
	FVector horizontal = GetActorRightVector() * axis.X;

	// �̵� ��ġ�� ����ȭ
	FVector normalizedVector = (vertical + horizontal).GetSafeNormal();

	// �÷��̾ �̵�
	SetActorLocation(GetActorLocation() + normalizedVector * GetMovementSpeed() * GetWorld()->GetDeltaSeconds());
}

void APlayerControls::CameraMovementAction(const FInputActionValue& value)
{
	FVector axis = value.Get<FVector>();

	float pitchDelta = axis.Y * 90.f * GetWorld()->GetDeltaSeconds();
	float yawDelta = axis.X * 90.f * GetWorld()->GetDeltaSeconds();

	mCamRotator.Pitch += pitchDelta;
	mCamRotator.Yaw += yawDelta;

	AdjustCamRotator(mCamRotator);

	mArm->SetRelativeRotation(mCamRotator);
}