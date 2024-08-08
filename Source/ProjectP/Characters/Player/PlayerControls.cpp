// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControls.h"

#include "../../InputData/PlayerInputData.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerAnimInstance.h"

#include "../../Data/Player/PlayerData.h"
#include "../../Inventory/Widget/InventoryWidget.h"
#include "../../Inventory/Item/Weapon/WeaponSword.h"

// Sets default values
APlayerControls::APlayerControls()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING_ARM"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	mCombat = CreateDefaultSubobject<UCombatComponent>(TEXT("COMBAT"));

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

	// DrawArrow();
	TraceForInteractable(DeltaTime);
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

	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetCharacterMovement());

	// 이동 속도 조정
	if (movement != nullptr)
		movement->MaxWalkSpeed = GameValue::GetMaxWalkSpeed();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	// 나는 무시
	mQueryParam.AddIgnoredActor(this);
}

void APlayerControls::BindInputActions(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	const UPlayerInputData* inputData = GetDefault<UPlayerInputData>();

	if (InputComponent == nullptr || inputData == nullptr)
		return;

	inputComponent->BindAction(inputData->mInputToMovement, ETriggerEvent::Triggered, this, &APlayerControls::MovementAction);
	inputComponent->BindAction(inputData->mInputToMovement, ETriggerEvent::Completed, this, &APlayerControls::CancelMovementAction);
	inputComponent->BindAction(inputData->mInputToCameraMovement, ETriggerEvent::Triggered, this, &APlayerControls::CameraMovementAction);
	inputComponent->BindAction(inputData->mInputToJump, ETriggerEvent::Started, this, &APlayerControls::JumpAction);
	inputComponent->BindAction(inputData->mInputToAttack, ETriggerEvent::Started, this, &APlayerControls::AttackAction);
	inputComponent->BindAction(inputData->mInputToFocus, ETriggerEvent::Triggered, this, &APlayerControls::FocusAction);
	inputComponent->BindAction(inputData->mInputToDrawSheath, ETriggerEvent::Triggered, this, &APlayerControls::DrawSheathAction);
	inputComponent->BindAction(inputData->mInputToInteract, ETriggerEvent::Triggered, this, &APlayerControls::InteractAction);
	inputComponent->BindAction(inputData->mInputToDodge, ETriggerEvent::Triggered, this, &APlayerControls::DodgeAction);
	inputComponent->BindAction(inputData->mInputToSprint, ETriggerEvent::Triggered, this, &APlayerControls::SprintAction);

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
	mInputVector = value.Get<FVector>();

	TryMovement();
}

void APlayerControls::CancelMovementAction(const FInputActionValue& value)
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
		Jump();
}

void APlayerControls::AttackAction(const FInputActionValue& value)
{
	if (!IsValid(mCombat))
		return;
	
	if(mCombat->GetIsAttacking())
		mCombat->SetIsAttackSaved(true);
	else
		TryAttack();
}

void APlayerControls::FocusAction(const FInputActionValue& value)
{

}

void APlayerControls::DrawSheathAction(const FInputActionValue& value)
{
	if(!CanPerformTogglingToCombat())
		return;

	bIsToggling = true;
	
	if(!IsValid(mCombat) || !IsValid(mCombat->GetMainWeapon()))
		return;

	PerformDrawSheath();
}

void APlayerControls::InteractAction(const FInputActionValue& value)
{
	if(!bEnableToInteract)
		return;

	IInteractable* interactable = Cast<IInteractable>(mHitResult.GetActor());

	if(interactable != nullptr)
		interactable->Interact(this);
}

void APlayerControls::DodgeAction(const FInputActionValue& value)
{
	TryDodge();
}

void APlayerControls::SprintAction(const FInputActionValue& value)
{
	TrySprint();
}

void APlayerControls::CancelSprintAction(const FInputActionValue& value)
{
	
}

void APlayerControls::InventoryAction(const FInputActionValue& value)
{
	mInventoryOpen = !mInventoryOpen;

	if(!mInventoryOpen)
		return;
	
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

void APlayerControls::TraceForInteractable(float deltaTime)
{
	mTraceStartPoint = GetActorLocation() - FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	mTraceEndPoint = mTraceStartPoint + GetActorForwardVector() * 120.f;
	
	bEnableToInteract = GetWorld()->SweepSingleByChannel(mHitResult, mTraceStartPoint, mTraceEndPoint, FQuat::Identity, ECC_GameTraceChannel3, FCollisionShape::MakeSphere(20.f), mQueryParam);

#if ENABLE_DRAW_DEBUG
	FColor drawColor = bEnableToInteract ? FColor::Red : FColor::Green;		// 감지되면 red 아니면 green

	DrawDebugCapsule(GetWorld(), (mTraceStartPoint + mTraceEndPoint) * .5f, 60.f, 20.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), drawColor, false, .02f);
#endif
}

bool APlayerControls::CanPerformTogglingToCombat()
{
	if(!IsValid(mCombat))
		return false;

	// 공격 중이 아니거나 전환 중이 아님
	return !mCombat->GetIsAttacking() && !bIsToggling;
}

bool APlayerControls::CanPerformTogglingToDodge()
{
	if(!IsValid(mCombat))
		return false;

	return !mCombat->GetIsDodge() && !bIsToggling;
}

void APlayerControls::TryMovement()
{
	// 공중일 때 || 착지했을 때 회전 막기
	if (mAnimInstance->GetIsInAir() || !mAnimInstance->GetIsLandingAnimEnd())
		return;

	PerformMovement();
}

void APlayerControls::PerformMovement()
{
	AdjustActorRotation();
	
	AddMovementInput(GetActorForwardVector());
}

void APlayerControls::TryInteract(const AActor* actor)
{
	
}

void APlayerControls::PerformDrawSheath()
{
	if (mCombat->GetMainWeapon()->GetIsEquipped())
		mAnimInstance->PlaySheathWeaponMontage();
	else
		mAnimInstance->PlayDrawWeaponMontage();
}

void APlayerControls::TryAttack()
{
	if(IsValid(mCombat) && IsValid(mCombat->GetMainWeapon()))
	{
		if(!CanPerformTogglingToCombat())
			return;
		
		PerformAttack(mCombat->GetAttackCount(), false);
	}
}

void APlayerControls::PerformAttack(int32 montageIndex, bool randomIndex)
{
	if(!IsValid(mCombat))
		return;

	if(!mCombat->GetCombatEnable())
	{
		PerformDrawSheath();
		return;	
	}
	
	mAnimInstance->PlayAttackMontage(montageIndex, randomIndex);

	mCombat->SetIsAttacking(true);	
	mCombat->IncreaseAttackCount();

}

void APlayerControls::TryDodge()
{
	if(!IsValid(mCombat))
		return;
	
	if(mCombat->GetIsDodge())
		PerformRoll();
	else	
		PerformDodge();
}

void APlayerControls::PerformDodge()
{
	if(!CanPerformTogglingToDodge())
		return;

	bIsToggling = true;
	
	// ESwordType type = ESwordType::None;
	//
	// if(mCombat->GetMainWeapon() == nullptr)
	// 	type = ESwordType::OneHand;
	// else
	// {
	// 	if(mCombat->GetMainWeapon()->IsA(AWeaponSword::StaticClass()))
	// 	{
	// 		AWeaponSword* sword = Cast<AWeaponSword>(mCombat->GetMainWeapon());
	// 		
	// 		type = !sword->GetIsEquipped() ? ESwordType::OneHand : sword->GetSwordData()->type;
	// 	}
	// }

	mCombat->SetIsDodge(true);
	// mAnimInstance->PlayDodgeMontage(type, false);
}

void APlayerControls::PerformRoll()
{
	// ESwordType type = ESwordType::None;
	//
	// if(mCombat->GetMainWeapon() == nullptr)
	// 	type = ESwordType::OneHand;
	// else
	// {
	// 	if(mCombat->GetMainWeapon()->IsA(AWeaponSword::StaticClass()))
	// 	{
	// 		AWeaponSword* sword = Cast<AWeaponSword>(mCombat->GetMainWeapon());
	// 		
	// 		type = !sword->GetIsEquipped() ? ESwordType::OneHand : sword->GetSwordData()->type;
	// 	}
	// }

	// mAnimInstance->PlayDodgeMontage(type, true);
}

void APlayerControls::TrySprint()
{
	if(mInputVector == FVector::ZeroVector)
		return;
}

bool APlayerControls::AddMoney(const FMoney* moneyData)
{
	if (!IsValid(mPlayerData))
		return false;

	if(mPlayerData->GetPlayerMoney() == GameValue::GetMaxMoney())
		return false;

	mPlayerData->SetPlayerMoney(mPlayerData->GetPlayerMoney() + moneyData->amount);

	if(mPlayerData->GetPlayerMoney() >= GameValue::GetMaxMoney())
		mPlayerData->SetPlayerMoney(GameValue::GetMaxMoney());

	return true;
}

void APlayerControls::ContinueAttack()
{
	if(!IsValid(mCombat))
		return;

	mCombat->SetIsAttacking(false);
	
	if(mCombat->GetIsAttackSaved())
	{
		mCombat->SetIsAttackSaved(false);
		
		TryAttack();
	}
}

void APlayerControls::EnableCombat()
{
	if(!IsValid(mCombat))
		return;

	bool combatEnable = !mCombat->GetCombatEnable();
	mCombat->SetCombatEnable(combatEnable);
}

void APlayerControls::ResetAttack()
{
	if(!IsValid(mCombat))
		return;

	mCombat->SetIsAttacking(false);
	mCombat->SetIsAttackSaved(false);
	mCombat->SetAttackCount(0);
}

void APlayerControls::DrawSheath()
{
	if(!IsValid(mCombat))
		return;
	
	ResetAttack();

	if(mCombat->GetMainWeapon()->GetIsEquipped())
		mCombat->GetMainWeapon()->OnUnequip();
	else
		mCombat->GetMainWeapon()->OnEquip();

	bIsToggling = false;
}

void APlayerControls::ResetDodge()
{
	if(!IsValid(mCombat))
		return;
	
	mCombat->SetIsDodge(false);

	bIsToggling = false;
}

void APlayerControls::ResetCombat()
{
	ResetAttack();
	ResetDodge();
}

void APlayerControls::PickUpItem(AItemBase* item)
{
	IEquippable* equippable = Cast<IEquippable>(item);

	if(equippable != nullptr)
	{
		if(!IsValid(mCombat))
			return;

		if(IsValid(mCombat->GetMainWeapon()))
			mCombat->GetMainWeapon()->Destroy();

		AWeaponBase* spawnWeapon = GetWorld()->SpawnActor<AWeaponBase>(item->GetThisItemData()->item_class);
		
		if(IsValid(spawnWeapon))
		{
			spawnWeapon->SetData(item->GetThisItemData(), false);
			spawnWeapon->SetSkeletalMesh(GetMesh());
			spawnWeapon->OnUnequip();
		
			mCombat->SetMainWeapon(spawnWeapon);
			mCombat->SetCombatEnable(false);
		}
	}
}

void APlayerControls::DrawArrow()
{
	FVector startLocation = GetActorLocation();
	FVector endLocation = startLocation + GetActorForwardVector() * 100.f;
	
	DrawDebugDirectionalArrow(GetWorld(), startLocation, endLocation, 120.f, FColor::Red, false, -1.f, 0.f, 3.f);
}
