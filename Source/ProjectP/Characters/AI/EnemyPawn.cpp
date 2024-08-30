// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPawn.h"

#include "../../Component/EnemyMovementComponent.h"
#include "../../Component/CombatComponent.h"
#include "../../Component/FocusComponent.h"

#include "EnemyController.h"
#include "EnemyAnimInstance.h"

#include "../../Data/EnemyStat.h"

#include "../../Inventory/Item/Weapon/WeaponSword.h"

AEnemyPawn::AEnemyPawn()
{
	mMovement = CreateDefaultSubobject<UEnemyMovementComponent>(TEXT("MOVEMENT"));
	mCombat = CreateDefaultSubobject<UCombatComponent>(TEXT("COMBAT"));
	mFocus = CreateDefaultSubobject<UFocusComponent>(TEXT("FOCUS"));

	mCapsule->SetCapsuleHalfHeight(89.f);
	mCapsule->SetCapsuleRadius(35.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -89.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mCapsule->SetCollisionProfileName(GameValue::GetEnemyFName());
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		meshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/EssentialAnimation/SwordShield/Demo/Mannequin/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));

	if(meshAsset.Succeeded())
		mMesh->SetSkeletalMesh(meshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		animAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Animations/AI/ABP_EnemyControls.ABP_EnemyControls_C'"));

	if(animAsset.Succeeded())
		mMesh->SetAnimInstanceClass(animAsset.Class);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		bloodAsset(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Blood/P_Blood_Splat_Cone.P_Blood_Splat_Cone'"));

	if(bloodAsset.Succeeded())
		mDamageParticle = bloodAsset.Object;
	
	AIControllerClass = AEnemyController::StaticClass();
}

// 지금은 사용하지 않아서 우선 주석 처리
// void AEnemyPawn::TryDrawSheath(const bool isEquipped) const
// {
// 	mAnimInstance->PlayDrawSheathMontage(isEquipped);
// }

void AEnemyPawn::PerformGuard() const
{
	if(!IsValid(mAnimInstance) || mAnimInstance->GetIsGuardingFlag())
		return;
	
	mAnimInstance->SetIsGuardingFlag(true);
}

void AEnemyPawn::ReleaseGuard() const
{
	if(!IsValid(mAnimInstance) || !mAnimInstance->GetIsGuardingFlag())
		return;
	
	mAnimInstance->SetIsGuardingFlag(false);
}

void AEnemyPawn::SetAimOffsetDegree(const float value) const
{
	if(IsValid(mAnimInstance))
		mAnimInstance->SetAimOffsetDegree(value);
}

void AEnemyPawn::SetMovementDegree(const float value) const
{
	if(IsValid(mAnimInstance))
		mAnimInstance->SetMovementDegree(value);
}

bool AEnemyPawn::IsDead() const
{
	if(IsValid(mEnemyStat))
		return mEnemyStat->IsCharacterDead();

	return false;
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	mMovement->MaxSpeed = 0.f;
	
	if(IsValid(mMesh->GetAnimInstance()))
		mAnimInstance = Cast<UEnemyAnimInstance>(mMesh->GetAnimInstance());
	
	InitWeapon();
	
	if(!IsValid(mEnemyStat))
	{
		mEnemyStat = NewObject<UEnemyStat>();

		if(IsValid(mEnemyStat))
			mEnemyStat->InitStat(this);
	}
}

float AEnemyPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float health = mEnemyStat->GetCurrCharacterHP() - DamageAmount;
	mEnemyStat->SetCurrCharacterHP(health);
	
	UE_LOG(ProjectP, Warning, TEXT("enemy health %f"), health);
	
	if(IsValid(mCombat))
	{
		if(mEnemyStat->GetCurrCharacterHP() <= 0)
			mCombat->EnableRagdoll(mMesh, mCapsule);
	}

	SetTakeDamage(EventInstigator->GetPawn());

	StartHitStop(.1f);
	mCombat->KnockBack(EventInstigator->GetPawn());
	
	return damage;
}

void AEnemyPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

FGenericTeamId AEnemyPawn::GetGenericTeamId() const
{
	return FGenericTeamId(mTeamID);
}

void AEnemyPawn::InitWeapon()
{
	FItem* swordItemData = CItemManager::GetInstance()->mItemTable->FindRow<FItem>(TEXT("Item_Weapon_004"), "");
	FItem* shieldItemData = CItemManager::GetInstance()->mItemTable->FindRow<FItem>(TEXT("Item_Weapon_007"), "");

	if(swordItemData == nullptr || shieldItemData == nullptr)
		return;

	AWeaponBase* spawnSword = GetWorld()->SpawnActor<AWeaponBase>(swordItemData->item_class);
	AWeaponBase* spawnShield = GetWorld()->SpawnActor<AWeaponBase>(shieldItemData->item_class);

	if(IsValid(spawnSword))
		spawnSword->SetData(swordItemData, false);

	if(IsValid(spawnShield))
		spawnShield->SetData(shieldItemData, false);

	IEquippable* swordEquippable = Cast<IEquippable>(spawnSword);
	IEquippable* shieldEquippable = Cast<IEquippable>(spawnShield);

	if(swordEquippable != nullptr && shieldEquippable != nullptr)
	{
		if(!IsValid(mCombat))
			return;

		if(IsValid(mCombat->GetMainWeapon()))
			mCombat->GetMainWeapon()->Destroy();
		
		if(IsValid(spawnSword))
		{
			spawnSword->SetOwner(this);
			spawnSword->SetSkeletalMesh(mMesh);
			spawnSword->OnUnequip();
		
			mCombat->SetMainWeapon(spawnSword);
			// mCombat->SetCombatEnable(false);
		}

		if(IsValid(spawnShield))
		{
			spawnShield->SetOwner(this);
			spawnShield->SetSkeletalMesh(mMesh);
			spawnShield->OnUnequip();
		
			mCombat->SetSubWeapon(spawnShield);
		}
	}

	spawnSword->OnEquip();
	spawnShield->OnEquip();
}

void AEnemyPawn::SetTakeDamage(const APawn* hitter)
{
	if(!IsValid(mAnimInstance) || !IsValid(hitter))
		return;

	ResetTakeDamage();

	if(IsValid(mRotate))
	{
		mAnimInstance->SetTakeDamageFlag(true);	
		mAnimInstance->SetTakeDamageDegree(mRotate->GetAngle(hitter));
	}
}

void AEnemyPawn::ContinueAttack()
{
}

void AEnemyPawn::DrawSheath()
{
	if(mCombat->GetMainWeapon() == nullptr)
		return;

	if(mCombat->GetMainWeapon()->GetIsEquipped())
		mCombat->GetMainWeapon()->OnUnequip();
	else
		mCombat->GetMainWeapon()->OnEquip();
}

void AEnemyPawn::EnableCombat()
{
}

void AEnemyPawn::ResetAttack()
{
	AEnemyController* controller = Cast<AEnemyController>(GetController());

	if(IsValid(controller))
	{
		UBlackboardComponent* blackBoardComp = controller->GetBlackboardComponent();

		if(IsValid(blackBoardComp))
			blackBoardComp->SetValueAsBool(GameValue::GetIsAttackingFName(), false);
	}
}

void AEnemyPawn::ResetCombat()
{
	ResetAttack();
	ResetTakeDamage();
}

void AEnemyPawn::ResetDodge()
{
}

void AEnemyPawn::ResetTakeDamage()
{
	mAnimInstance->SetTakeDamageFlag(false);
}

void AEnemyPawn::ResetMontage()
{
}

void AEnemyPawn::TakeDamage(APawn* hitterPawn)
{
	if(mEnemyStat->IsCharacterDead())
		return;

	if(!IsValid(hitterPawn))
		return;
	
	FDamageEvent damageEvent;

	UCombatComponent* hitterCombatComp = hitterPawn->FindComponentByClass<UCombatComponent>();

	if(IsValid(hitterCombatComp) && !hitterCombatComp->IsMainWeaponNull())
		TakeDamage(hitterCombatComp->GetMainWeaponAbilityValue(), damageEvent, hitterPawn->GetController(), hitterCombatComp->GetMainWeapon());
}

void AEnemyPawn::SpawnEmitter(FHitResult result)
{
	UParticleSystemComponent* particleSystemComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mDamageParticle, result.ImpactPoint, result.ImpactNormal.Rotation(), true);

	if(IsValid(particleSystemComp))
		particleSystemComp->SetRelativeScale3D(particleSystemComp->GetRelativeScale3D() * .5f);
}

void AEnemyPawn::StartHitStop(const float time)
{
	GetWorldSettings()->SetTimeDilation(time);
	GetWorld()->GetTimerManager().SetTimer(mHitStopTimeHandle, this, &AEnemyPawn::EndHitStop, GetWorld()->GetDeltaSeconds(), false);
}

void AEnemyPawn::EndHitStop()
{
	GetWorld()->GetTimerManager().ClearTimer(mHitStopTimeHandle);
	GetWorldSettings()->SetTimeDilation(1.f);
}