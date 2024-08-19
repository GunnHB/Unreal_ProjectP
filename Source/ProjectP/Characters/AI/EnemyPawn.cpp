// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "../../Component/EnemyMovementComponent.h"
#include "../../Component/CombatComponent.h"

#include "EnemyAnimInstance.h"
#include "EnemyController.h"

#include "../../Inventory/Item/Weapon/WeaponSword.h"

AEnemyPawn::AEnemyPawn()
{
	mMovement = CreateDefaultSubobject<UEnemyMovementComponent>(TEXT("MOVEMENT"));
	mCombat = CreateDefaultSubobject<UCombatComponent>(TEXT("COMBAT"));

	mCapsule->SetCapsuleHalfHeight(89.f);
	mCapsule->SetCapsuleRadius(22.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -89.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mCapsule->SetCollisionProfileName(GameValue::GetEnemyFName());

	mEnemyStat = NewObject<UEnemyStat>();
	
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

void AEnemyPawn::TryDrawSheath(const bool isEquipped) const
{
	mAnimInstance->PlayDrawSheathMontage(isEquipped);
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	mMovement->MaxSpeed = 0.f;
	
	if(IsValid(mMesh->GetAnimInstance()))
		mAnimInstance = Cast<UEnemyAnimInstance>(mMesh->GetAnimInstance());
	
	InitWeapon();
}

float AEnemyPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float health = mEnemyStat->GetCharacterHealth() - DamageAmount;
	mEnemyStat->SetCharacterHealth(health);
	
	UE_LOG(ProjectP, Warning, TEXT("health %f"), health);
	
	if(IsValid(mCombat))
	{
		if(mEnemyStat->GetCharacterHealth() <= 0)
			mCombat->EnableRagdoll(mMesh, mCapsule);
	}

	StartHitStop(.1f);
	mCombat->KnockBack(EventInstigator->GetPawn());
	
	return damage;
}

void AEnemyPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AEnemyPawn::InitWeapon()
{
	FItem* itemData = CItemManager::GetInstance()->mItemTable->FindRow<FItem>(TEXT("Item_Weapon_004"), "");

	if(itemData == nullptr)
		return;

	AWeaponBase* spawnWeapon = GetWorld()->SpawnActor<AWeaponBase>(itemData->item_class);

	if(IsValid(spawnWeapon))
		spawnWeapon->SetData(itemData, false);

	IEquippable* equippable = Cast<IEquippable>(spawnWeapon);

	if(equippable != nullptr)
	{
		if(!IsValid(mCombat))
			return;

		if(IsValid(mCombat->GetMainWeapon()))
			mCombat->GetMainWeapon()->Destroy();
		
		if(IsValid(spawnWeapon))
		{
			spawnWeapon->SetOwner(this);
			spawnWeapon->SetSkeletalMesh(mMesh);
			spawnWeapon->OnUnequip();
		
			mCombat->SetMainWeapon(spawnWeapon);
			mCombat->SetCombatEnable(false);
		}
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
}

void AEnemyPawn::ResetCombat()
{
}

void AEnemyPawn::ResetDodge()
{
}

void AEnemyPawn::ResetTakeDamage()
{
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