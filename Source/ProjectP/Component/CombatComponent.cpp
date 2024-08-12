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
