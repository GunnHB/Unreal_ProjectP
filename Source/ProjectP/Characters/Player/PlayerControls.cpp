// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControls.h"

#include "../../InputData/PlayerInputData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerAnimInstance.h"

#include "../../Data/Player/PlayerData.h"

#include "../../Inventory/Widget/InventoryWidget.h"

#include "../../Inventory/Item/Equipment/Weapon/OneHandSword.h"

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

	SpawnWeapon();
}

// Called every frame
void APlayerControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawArrow();
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
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		meshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Quinn_Weapon.SKM_Quinn_Weapon'"));

	if (meshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(meshAsset.Object);

	// animinstance
	static ConstructorHelpers::FClassFinder<UAnimInstance>
		animAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Animations/ABP_PlayerControls.ABP_PlayerControls_C'"));

	if (animAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(animAsset.Class);

	// inventory
	static ConstructorHelpers::FClassFinder<UUserWidget>
		invenAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/04_Inventory/Widget/UI_Inventory.UI_Inventory_C'"));

	if(invenAsset.Succeeded())
		mInventoryWidgetClass = invenAsset.Class;

	// playerdata
	mPlayerData = NewObject<UPlayerData>();
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

	// 컨트롤러의 회전에 영향을 받지 않도록
	bUseControllerRotationYaw = false;

	// 이동 속도 조정
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetCharacterMovement());

	if (movement != nullptr)
		movement->MaxWalkSpeed = 500.f;

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
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
	inputComponent->BindAction(inputData->mInputToDrawWeapon, ETriggerEvent::Triggered, this, &APlayerControls::DrawWeaponAction);

	inputComponent->BindAction(inputData->mInputToInventory, ETriggerEvent::Triggered, this, &APlayerControls::InventoryAction);
}

void APlayerControls::MappingContext() const
{
	APlayerController* player = Cast<APlayerController>(GetController());

	if (player == nullptr)
		return;

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player->GetLocalPlayer());
	const UPlayerInputData* inputData = GetDefault<UPlayerInputData>();

	subsystem->AddMappingContext(inputData->mContext, 0);
}

void APlayerControls::MovementAction(const FInputActionValue& value)
{
	// 공중에서는 이동 막기
	if (mAnimInstance->GetIsInAir())
		return;

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
	if (CanJump())
	{
		mAnimInstance->PlayJumpAnim();
		Jump();
	}
}

void APlayerControls::AttackAction(const FInputActionValue& value)
{

}

void APlayerControls::SprintAction(const FInputActionValue& value)
{
	
}

void APlayerControls::FocusAction(const FInputActionValue& value)
{

}

void APlayerControls::DrawWeaponAction(const FInputActionValue& value)
{
	if(!IsValid(mMainWeapon))
		return;

	mMainWeapon->GetIsEquipped() ? mMainWeapon->OnUnequipped("SwordHipAttachSocket") : mMainWeapon->OnEquipped("WeaponSocket");
}

void APlayerControls::InventoryAction(const FInputActionValue& value)
{
	mInventoryOpen = !mInventoryOpen;

	if(!mInventoryOpen)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, TEXT("I on our keyboard has been pressed"));

	if(IsValid(mInventoryWidgetClass))
	{
		if(!IsValid(mInventoryWidget))
			mInventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), mInventoryWidgetClass);

		mInventoryWidget->AddToViewport();
	}
}

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

	// targetAngle 조정
	if (targetAngle < -180.f)
		targetAngle = 360 + targetAngle;
	else if (targetAngle > 180.f)
		targetAngle = targetAngle - 360.f;

	FRotator targetRotation = FRotator(0.f, targetAngle, 0.f);
	// 회전 보간
	// interpspeed 값이 클수록 빠르게 회전
	FRotator rotation = FMath::RInterpTo(GetActorRotation(), targetRotation, GetWorld()->GetDeltaSeconds(), 10.f);

	// 최종적으로 회전
	SetActorRotation(rotation);
}

void APlayerControls::DrawArrow()
{
	FVector startLocation = GetActorLocation();
	FVector endLocation = startLocation + GetActorForwardVector() * 100.f;
	
	DrawDebugDirectionalArrow(GetWorld(), startLocation, endLocation, 120.f, FColor::Red, false, -1.f, 0.f, 3.f);
}

void APlayerControls::SpawnWeapon()
{
	AOneHandSword* sword = GetWorld()->SpawnActor<AOneHandSword>(FVector::ZeroVector, FRotator::ZeroRotator);

	if(!IsValid(sword))
		return;

	// 메인 무기로 세팅
	mMainWeapon = sword;
	
	sword->SetSkeletalMesh(GetMesh());
	sword->OnUnequipped("SwordHipAttachSocket");
}

bool APlayerControls::AddMoney(const FMoney* moneyData)
{
	if (!IsValid(mPlayerData))
		return false;

	if(mPlayerData->GetPlayerMoney() == GameValue::GetMaxMoney())
		return false;

	mPlayerData->SetPlayerMoney(mPlayerData->GetPlayerMoney() + moneyData->Amount);

	if(mPlayerData->GetPlayerMoney() >= GameValue::GetMaxMoney())
		mPlayerData->SetPlayerMoney(GameValue::GetMaxMoney());

	return true;
}

void APlayerControls::NormalAttack()
{
	
}
