// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

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
		
	++mAttackCount;

	if(mAttackCount >= arraySize)
		mAttackCount = 0;
}

float UCombatComponent::GetMainWeaponAbilityValue() const
{
	if(!IsValid(mMainWeapon))
		return 0.f;

	return mMainWeapon->GetWeaponData()->ability_value;
}

void UCombatComponent::KnockBack(const AActor* hitter)
{
	if(!IsValid(hitter))
		return;
	
	FVector direction = GetOwner()->GetActorLocation() - hitter->GetActorLocation();

	if(direction.Normalize())
	{
		mKnockBackTarget = GetOwner()->GetActorLocation() + direction * GameValue::GetKnockBackAmount();
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
	
	// mesh->AddImpulse(mKnockBackTarget * 5000.f);
	
	capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCombatComponent::InterpActorLocation()
{
	if((mKnockBackTarget - GetOwner()->GetActorLocation()).Size() < 0.01f)
	{
		GetWorld()->GetTimerManager().ClearTimer(mInterpTimeHandle);
		mKnockBackTarget = FVector::ZeroVector;
		
		return;
	}
	
	FVector knockBackLocation = FMath::VInterpTo(GetOwner()->GetActorLocation(), mKnockBackTarget, GetWorld()->GetDeltaSeconds(), 10.f);
	GetOwner()->SetActorRelativeLocation(knockBackLocation);
}
