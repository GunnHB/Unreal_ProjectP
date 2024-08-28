// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControls.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerAnimInstance.h"

#include "../../InputData/PlayerInputData.h"

#include "../../Inventory/Widget/InventoryWidget.h"

#include "../../Data/PlayerStat.h"

#include "../../Component/CombatComponent.h"
#include "../../Component/StateManageComponent.h"
#include "../../Component/RotateComponent.h"
#include "../../Component/FocusComponent.h"

#include "InGamePlayerController.h"

APlayerControls::APlayerControls()
{
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRING_ARM"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	mCombat = CreateDefaultSubobject<UCombatComponent>(TEXT("COMBAT"));
	mStateManage = CreateDefaultSubobject<UStateManageComponent>(TEXT("STATE_MANAGE"));
	mRotate = CreateDefaultSubobject<URotateComponent>(TEXT("ROTATE"));
	mFocus = CreateDefaultSubobject<UFocusComponent>(TEXT("FOCUS"));

	InitAssets();
	InitComponentsValue();
}

void APlayerControls::BeginPlay()
{
	Super::BeginPlay();
	
	mAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	mStateManage->SetState(ECharacterState::General);

	if(IsValid(mPlayerStat))
		mPlayerStat->InitStat(this);
	
	MappingContext();
}

void APlayerControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(mPlayerStat->IsCharacterDead())
		return;

#if ENABLE_DRAW_DEBUG
	DrawArrow();
#endif
	
	GetAimOffsetX();
	TraceForInteractable();

	CalcStaminaRecoveryTime(DeltaTime);
}

void APlayerControls::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindInputActions(PlayerInputComponent);
}

float APlayerControls::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float health = mPlayerStat->GetCurrCharacterHP() - DamageAmount;
	mPlayerStat->SetCurrCharacterHP(health);
	
	UE_LOG(ProjectP, Warning, TEXT("player health %f"), health);
	
	if(IsValid(mCombat))
	{
		if(mPlayerStat->GetCurrCharacterHP() <= 0)
		{
			if(IsValid(mStateManage))
				mStateManage->SetState(ECharacterState::Dead);
			
			mCombat->EnableRagdoll(GetMesh(), GetCapsuleComponent());
			mSpringArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GameValue::GetPelvisSocketName());
			
			return damage;
		}
		
		if(IsValid(mStateManage))
			mStateManage->SetState(ECharacterState::TakeDamage);
	}

	StartHitStop(.01f);
	
	SetDamageDegree(EventInstigator->GetPawn());
	mCombat->KnockBack(EventInstigator->GetPawn());

	AInGamePlayerController* controller = Cast<AInGamePlayerController>(GetController());
	
	return damage;
}

FGenericTeamId APlayerControls::GetGenericTeamId() const
{
	return FGenericTeamId(mTeamID);
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
		invenAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/03_UI/Widget/UI_Inventory.UI_Inventory_C'"));

	if(invenAsset.Succeeded())
		mInventoryWidgetClass = invenAsset.Class;
	
	// playerStat
	mPlayerStat = NewObject<UPlayerStat>();
}

void APlayerControls::InitComponentsValue()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(89.f);
	GetCapsuleComponent()->SetCapsuleRadius(35.f);

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
		movement->MaxWalkSpeed = GameValue::GetJogSpeed();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionProfileName(GameValue::GetPlayerFName());

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
	inputComponent->BindAction(inputData->mInputToLightAttack, ETriggerEvent::Triggered, this, &APlayerControls::LightAttackAction);
	inputComponent->BindAction(inputData->mInputToHeavyAttack, ETriggerEvent::Triggered, this, &APlayerControls::HeavyAttackAction);
	inputComponent->BindAction(inputData->mInputToFocus, ETriggerEvent::Triggered, this, &APlayerControls::FocusAction);
	inputComponent->BindAction(inputData->mInputToFocus, ETriggerEvent::Completed, this, &APlayerControls::CancelFocusAction);
	inputComponent->BindAction(inputData->mInputToDrawSheath, ETriggerEvent::Triggered, this, &APlayerControls::DrawSheathAction);
	inputComponent->BindAction(inputData->mInputToInteract, ETriggerEvent::Triggered, this, &APlayerControls::InteractAction);
	inputComponent->BindAction(inputData->mInputToDodge, ETriggerEvent::Triggered, this, &APlayerControls::DodgeAction);
	inputComponent->BindAction(inputData->mInputToSprint, ETriggerEvent::Triggered, this, &APlayerControls::SprintAction);
	inputComponent->BindAction(inputData->mInputToSprint, ETriggerEvent::Completed, this, &APlayerControls::CancelSprintAction);

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
	mLastInputVector = mInputVector;

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
	// if (CanJump())
	// 	Jump();
}

void APlayerControls::LightAttackAction(const FInputActionValue& value)
{
	if(!IsValid(mStateManage))
		return;

	if(mStateManage->IsCurrentStateEqual(ECharacterState::Attack))
	{
		mCombat->SetIsAttackSaved(true);
		return;	
	}

	TryAttack();
}

void APlayerControls::HeavyAttackAction(const FInputActionValue& value)
{

}

void APlayerControls::FocusAction(const FInputActionValue& value)
{
	if(IsValid(mStateManage))
	{
		mStateManage->ResetState();
		mStateManage->SetAction(ECharacterAction::Guard);
	}
	
	bIsFocusing = true;

	if(IsValid(mFocus))
		mFocus->TryFocus(mRotate->GetForwardVectorByUnitAxis(mCamera, EAxis::X));
}

void APlayerControls::CancelFocusAction(const FInputActionValue& value)
{
	if(IsValid(mStateManage))
	{
		mStateManage->ResetState();
		mStateManage->SetAction(ECharacterAction::General);
	}
	
	bIsFocusing = false;

	if(IsValid(mFocus))
		mFocus->ResetTargetActor();

	mAnimInstance->ResetDegreeValue();
}

void APlayerControls::DrawSheathAction(const FInputActionValue& value)
{
	TryDrawSheath();
}

void APlayerControls::InteractAction(const FInputActionValue& value)
{
	TryInteract();
}

void APlayerControls::DodgeAction(const FInputActionValue& value)
{
	// TryDodge();
}

void APlayerControls::SprintAction(const FInputActionValue& value)
{
	TrySprint();
}

void APlayerControls::CancelSprintAction(const FInputActionValue& value)
{
	SetCurrentMovementType(ECharacterMovementType::Jog);

	bIsStaminaRecovery = true;
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
	FVector direction = bIsFocusing ? FVector::ZeroVector : mInputVector.GetSafeNormal();

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

void APlayerControls::TraceForInteractable()
{
	mTraceStartPoint = GetActorLocation() - FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	mTraceEndPoint = mTraceStartPoint + GetActorForwardVector() * 120.f;
	
	bEnableToInteract = GetWorld()->SweepSingleByChannel(mHitResult, mTraceStartPoint, mTraceEndPoint, FQuat::Identity, ECC_GameTraceChannel3, FCollisionShape::MakeSphere(20.f), mQueryParam);

#if ENABLE_DRAW_DEBUG
	FColor drawColor = bEnableToInteract ? FColor::Red : FColor::Green;		// 감지되면 red 아니면 green

	DrawDebugCapsule(GetWorld(), (mTraceStartPoint + mTraceEndPoint) * .5f, 60.f, 20.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), drawColor, false, .02f);
#endif
}

bool APlayerControls::CanPerformMove()
{
	if(!IsValid(mStateManage))
		return false;

	return mStateManage->IsCurrentStateEqual(ECharacterState::General);
}

bool APlayerControls::CanPerformAttack()
{
	if(!IsValid(mStateManage))
		return false;

	TArray<int8> stateArray = {static_cast<int8>(ECharacterState::Dodge), static_cast<int8>(ECharacterState::Dead)};

	return mStateManage->IsCurrentValueNotEqualToAny(stateArray);
}

bool APlayerControls::CanPerformDodge()
{
	if(!IsValid(mStateManage))
		return false;

	TArray<int8> stateArray = {static_cast<int8>(ECharacterState::Dodge), static_cast<int8>(ECharacterState::Dead)};

	return mStateManage->IsCurrentValueNotEqualToAny(stateArray);
}

bool APlayerControls::CanPerformTakeDamage()
{
	if(!IsValid(mStateManage))
		return false;

	return !mStateManage->IsCurrentStateEqual(ECharacterState::Dead);
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
	
	if(bIsFocusing)
	{
		AddMovementInput(GetActorForwardVector(), mInputVector.Y);
		AddMovementInput(GetActorRightVector(), mInputVector.X);
	}
	else
		AddMovementInput(GetActorForwardVector());
}

void APlayerControls::TryDrawSheath()
{
	if(!IsValid(mCombat) || mCombat->IsMainWeaponNull())
		return;
	
	PerformDrawSheath();
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
	if(IsValid(mCombat) && !mCombat->IsMainWeaponNull())
		PerformAttack(mCombat->GetAttackIndex(), false, ECharacterAction::LightAttack);
}

void APlayerControls::PerformAttack(int32 montageIndex, bool randomIndex, const ECharacterAction attackType)
{
	if(!IsValid(mCombat))
		return;

	if(!CanPerformAttack())
		return;

	if(!mCombat->GetCombatEnable())
	{
		PerformDrawSheath();
		return;
	}

	if(mCombat->GetIsKnockBack())
		return;

	if(mPlayerStat->GetIsExhausted())
		return;

	if(mPlayerStat->GetStaminaPercentage() <= 0.f)
	{
		mPlayerStat->SetIsExhausted(true);
		return;
	}

	mAnimInstance->PlayAttackMontage(montageIndex, randomIndex);
	
	mStateManage->SetState(ECharacterState::Attack);
	mStateManage->SetAction(attackType);
	
	mCombat->IncreaseAttackCount();

	RefreshStaminaValue(30.f);
	bIsStaminaRecovery = false;
}

void APlayerControls::TryDodge()
{
	if(!IsValid(mStateManage))
		return;
	
	if(mStateManage->IsCurrentStateEqual(ECharacterState::Dodge))
		PerformRoll();
	else
		PerformDodge();
}

void APlayerControls::PerformDodge()
{
	if(!CanPerformDodge())
		return;

	if(IsValid(mAnimInstance))
	{
		mAnimInstance->PerformStopAllMontages();
		ResetCombat();
	}
	
	mStateManage->SetState(ECharacterState::Dodge);
	mStateManage->SetAction(ECharacterAction::Dodge);
}

void APlayerControls::PerformRoll()
{
	
}

void APlayerControls::TrySprint()
{
	if(mInputVector == FVector::ZeroVector)
		return;

	if(mPlayerStat->GetIsExhausted())
		return;
	
	if(mPlayerStat->GetStaminaPercentage() <= 0.f)
	{
		SetCurrentMovementType(ECharacterMovementType::Jog);
		mPlayerStat->SetIsExhausted(true);
		
		return;
	}
	
	SetCurrentMovementType(ECharacterMovementType::Sprint);
	RefreshStaminaValue();
	
	bIsStaminaRecovery = false;
}

void APlayerControls::TryInteract()
{
	if(!bEnableToInteract)
		return;

	PerformInteract();
}

void APlayerControls::PerformInteract()
{
	IInteractable* interactable = Cast<IInteractable>(mHitResult.GetActor());

	if(interactable != nullptr)
		interactable->Interact(this);
}

void APlayerControls::PerformAction(const ECharacterState state, const ECharacterAction action) const
{
	if(IsValid(mStateManage))
	{
		mStateManage->SetState(state);
		mStateManage->SetAction(action);
	}
}

float APlayerControls::GetDegree(const FVector& vector) const
{
	if(!bIsFocusing)
		return 0.f;
	
	FVector forwardVector = GetActorForwardVector() * vector.Y;
	FVector rightVector = GetActorRightVector() * vector.X;
	FVector targetVector = rightVector + forwardVector;

	return mRotate->GetAngleToTargetForward(targetVector);
}

void APlayerControls::CalcStaminaRecoveryTime(const float deltaTime)
{
	if(!bIsStaminaRecovery)
	{
		bCalcStaminaRecovery = true;
		return;
	}

	float targetTime = mPlayerStat->GetIsExhausted() ? mExhaustRecoveryTime : mStaminaRecoveryTime;

	if(mRecoveryElapsedTime < targetTime && bCalcStaminaRecovery)
		mRecoveryElapsedTime += deltaTime;
	else
	{
		bCalcStaminaRecovery = false;
		mRecoveryElapsedTime = 0.f;
		
		RefreshStaminaValue(-1.f);
	}
}

void APlayerControls::RefreshStaminaValue(const float decreaseValue)
{
	float currentStamina = mPlayerStat->GetCurrCharacterStamina();
	currentStamina -= decreaseValue * .5f;

	mPlayerStat->SetCurrCharacterStamina(currentStamina);
	
	AInGamePlayerController* playerController = Cast<AInGamePlayerController>(GetController());
	
	if(IsValid(playerController))
		playerController->SetPlayerStamina(mPlayerStat->GetStaminaPercentage(), mPlayerStat->GetIsExhausted());
	
	bIsStaminaRecovery = mPlayerStat->GetStaminaPercentage() < 1.f;

	if(mPlayerStat->GetIsExhausted())
		mPlayerStat->SetIsExhausted(mPlayerStat->GetStaminaPercentage() < 1.f);
}

void APlayerControls::SetDamageDegree(const AActor* hitter)
{
	mDamageDegree = mRotate->GetAngle(hitter);
}

void APlayerControls::SetCurrentMovementType(const ECharacterMovementType type)
{
	if(type == mCurrentMovementType)
		return;

	mCurrentMovementType = type;
	SetMovementSpeed();
}

void APlayerControls::SetMovementSpeed()
{
	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(GetMovementComponent());

	if(!IsValid(movement))
		return;
	
	switch (mCurrentMovementType)
	{
	case ECharacterMovementType::Walk:
		movement->MaxWalkSpeed = GameValue::GetWalkSpeed();
		break;
	case ECharacterMovementType::Jog:
		movement->MaxWalkSpeed = GameValue::GetJogSpeed();
		break;
	case ECharacterMovementType::Sprint:
		movement->MaxWalkSpeed = GameValue::GetSprintSpeed();
		break;
	}
}

bool APlayerControls::AddMoney(const FMoney* moneyData)
{
	if (!IsValid(mPlayerStat))
		return false;

	if(mPlayerStat->GetPlayerMoney() == GameValue::GetMaxMoney())
		return false;

	mPlayerStat->SetPlayerMoney(mPlayerStat->GetPlayerMoney() + moneyData->amount);

	if(mPlayerStat->GetPlayerMoney() >= GameValue::GetMaxMoney())
		mPlayerStat->SetPlayerMoney(GameValue::GetMaxMoney());

	return true;
}

void APlayerControls::ContinueAttack()
{
	if(!IsValid(mCombat))
		return;
	
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

void APlayerControls::DrawSheath()
{
	if(!IsValid(mCombat))
		return;
	
	ResetAttack();

	if(mCombat->GetMainWeapon()->GetIsEquipped())
		mCombat->GetMainWeapon()->OnUnequip();
	else
		mCombat->GetMainWeapon()->OnEquip();
}

void APlayerControls::ResetAttack()
{
	if(!IsValid(mCombat))
		return;

	mCombat->SetIsAttackSaved(false);
	mCombat->SetAttackIndex(0);

	bIsStaminaRecovery = true;
}

void APlayerControls::ResetDodge()
{
	if(IsValid(mStateManage))
		mStateManage->ResetState();
}

void APlayerControls::ResetTakeDamage()
{
	if(IsValid(mStateManage))
		mStateManage->ResetState();
}

void APlayerControls::ResetMontage()
{
	if(IsValid(mAnimInstance))
		mAnimInstance->PerformStopAllMontages();
}

void APlayerControls::StartHitStop(const float time)
{
	GetWorldSettings()->SetTimeDilation(time);
	GetWorld()->GetTimerManager().SetTimer(mHitStopTimeHandle, this, &APlayerControls::EndHitStop, GetWorld()->GetDeltaSeconds() / 100, false);
}

void APlayerControls::EndHitStop()
{
	GetWorld()->GetTimerManager().ClearTimer(mHitStopTimeHandle);
	GetWorldSettings()->SetTimeDilation(1.f);
}

void APlayerControls::ResetCombat()
{
	if(IsValid(mStateManage))
	{
		mStateManage->ResetState();
		mStateManage->ResetAction();
	}
	
	ResetAttack();
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
			spawnWeapon->SetOwner(this);
			spawnWeapon->SetData(item->GetThisItemData(), false);
			spawnWeapon->SetSkeletalMesh(GetMesh());
			spawnWeapon->OnUnequip();
		
			mCombat->SetMainWeapon(spawnWeapon);
			mCombat->SetCombatEnable(false);
		}
	}
}

void APlayerControls::TakeDamage(APawn* hitterPawn)
{
	if(mPlayerStat->IsCharacterDead())
		return;

	if(!IsValid(hitterPawn))
		return;

	if(!CanPerformTakeDamage())
		return;

	FDamageEvent damageEvent;

	UCombatComponent* hitterCombatComp = hitterPawn->FindComponentByClass<UCombatComponent>();

	if(IsValid(hitterCombatComp) && !hitterCombatComp->IsMainWeaponNull())
		TakeDamage(hitterCombatComp->GetMainWeaponAbilityValue(), damageEvent, hitterPawn->GetController(), hitterCombatComp->GetMainWeapon());
}

void APlayerControls::SpawnEmitter(FHitResult result)
{
}

float APlayerControls::GetInputDegree() const
{
	return GetDegree(mInputVector);
}

float APlayerControls::GetLastDegree() const
{
	return GetDegree(mLastInputVector);
}

float APlayerControls::GetAimOffsetX() const
{
	if(bIsFocusing)
	{
		if(IsValid(mRotate))
			return mRotate->GetAngleToTargetForward(mCamera->GetForwardVector());
	}

	return 0.f;
}

#if ENABLE_DRAW_DEBUG
void APlayerControls::DrawArrow() const
{
	FVector startLocation = GetActorLocation();
	FVector endLocation = startLocation + GetActorForwardVector() * 100.f;
	
	DrawDebugDirectionalArrow(GetWorld(), startLocation, endLocation, 120.f, FColor::Red, false, -1.f, 0.f, 3.f);

	FVector camEndLocation = startLocation + mRotate->GetForwardVectorByUnitAxis(mCamera, EAxis::X) * 150.f;
	DrawDebugDirectionalArrow(GetWorld(), startLocation, camEndLocation, 120.f, FColor::Blue, false, -1.f, 0.f, 3.f);
}
#endif