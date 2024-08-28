// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "CollisionComponent.h"
#include "../Characters/AnimInstanceBase.h"
#include "../Inventory/Item/Weapon/WeaponSword.h"

void UCombatComponent::IncreaseAttackCount()
{
	if(!IsValid(mMainWeapon))
		return;

	int32 arraySize = 0;
	
	if(Cast<AWeaponSword>(mMainWeapon))
		arraySize = Cast<AWeaponSword>(mMainWeapon)->GetSwordData()->montage_attack_array.Num();

	if(arraySize == 0)
		return;
		
	++mAttackIndex;

	if(mAttackIndex >= arraySize)
		mAttackIndex = 0;
}

float UCombatComponent::GetMainWeaponAbilityValue() const
{
	if(!IsValid(mMainWeapon))
		return 0.f;

	return mMainWeapon->GetWeaponData()->ability_value;
}

UCollisionComponent* UCombatComponent::GetMainCollisionComp() const
{
	if(IsMainWeaponNull())
		return nullptr;

	return mMainWeapon->FindComponentByClass<UCollisionComponent>();
}

void UCombatComponent::KnockBack(const AActor* hitter)
{
	if(!IsValid(hitter))
		return;

	FVector hitterLocation = FVector(hitter->GetActorLocation().X, hitter->GetActorLocation().Y, 0.f);
	FVector ownerLocation = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, 0.f);
	
	FVector direction = ownerLocation - hitterLocation;

	if(direction.Normalize())
	{
		bIsKnockBack = true;
		
		mKnockBackDirection = GetOwner()->GetActorLocation() + direction * GameValue::GetKnockBackAmount();
		GetWorld()->GetTimerManager().SetTimer(mInterpTimeHandle, this, &UCombatComponent::InterpActorLocation, GetWorld()->GetDeltaSeconds(), true, -1);
		
#if ENABLE_DRAW_DEBUG
		FVector start = GetOwner()->GetActorLocation();
		FVector end = start + direction * 100.f;
		
		DrawDebugDirectionalArrow(GetWorld(), start, end, 120.f, FColor::Green, false, 5.f, 0.f, 3.f);
#endif
	}
}

void UCombatComponent::EnableRagdoll(USkeletalMeshComponent* mesh, UCapsuleComponent* capsule) const
{
	if(!IsValid(mesh) || !IsValid(capsule))
		return;
	
	mesh->SetCollisionProfileName(TEXT("Ragdoll"));
	mesh->SetSimulatePhysics(true);
	
	mesh->AddImpulse(mKnockBackDirection * 5.f);
	
	capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCombatComponent::InterpActorLocation()
{
	// 약간 보정
	if((mKnockBackDirection - GetOwner()->GetActorLocation()).Size() <= 0.1f)
	{
		GetWorld()->GetTimerManager().ClearTimer(mInterpTimeHandle);
		mKnockBackDirection = FVector::ZeroVector;

		bIsKnockBack = false;
		
		return;
	}
	
	FVector knockBackLocation = FMath::VInterpTo(GetOwner()->GetActorLocation(), mKnockBackDirection, GetWorld()->GetDeltaSeconds(), 10.f);
	GetOwner()->SetActorRelativeLocation(knockBackLocation);
}

void UCombatComponent::PerformAttack(UAnimInstanceBase* animInstance)
{
	if(IsValid(animInstance))
	{
		TArray<UAnimMontage*> montageArray = CItemManager::GetInstance()->mSwordTable->FindRow<FSword>(mMainWeapon->GetWeaponData()->ref_row_name, "")->montage_attack_array;

		if(montageArray.Num() != 0)
			animInstance->PlayAttackMontage(montageArray, mAttackIndex, bIsRandomAttack);
	}
}

void UCombatComponent::PerformAttack(class UAnimInstanceBase* animInstance, const TArray<UAnimMontage*>& attackMontageArray)
{
	if(IsValid(animInstance))
	{
		if(attackMontageArray.Num() != 0)
			animInstance->PlayAttackMontage(attackMontageArray, mAttackIndex, bIsRandomAttack);
	}
}
