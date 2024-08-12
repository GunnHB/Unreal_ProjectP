// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	TObjectPtr<class AWeaponBase> mMainWeapon = nullptr;
	TObjectPtr<class AWeaponBase> mSubWeapon = nullptr;

	TSubclassOf<class AWeaponBase> mMainWeaponClass = nullptr;
	TSubclassOf<class AWeaponBase> mSubWeaponClass = nullptr;

	// attack
	bool bIsCombatEnable = false;
	bool bIsAttackSaved = false;
	bool bIsAttacking = false;
	int32 mAttackCount = 0;

	// dodge / roll
	bool bIsDodge = false;

	// take damage
	bool bTakeDamage = false;

public:	
	// getter
	bool GetCombatEnable() const {return bIsCombatEnable;}
	bool GetIsAttacking() const {return bIsAttacking;}
	bool GetIsAttackSaved() const {return bIsAttackSaved;}
	AWeaponBase* GetMainWeapon() const {return mMainWeapon;}
	int32 GetAttackCount() const {return mAttackCount;}

	bool GetIsDodge() const {return bIsDodge;}

	bool GetTakeDamage() const {return bTakeDamage;}
	
	// setter
	void SetCombatEnable(bool value) {bIsCombatEnable = value;}
	void SetIsAttacking(bool value) {bIsAttacking = value;}
	void SetIsAttackSaved(bool value) {bIsAttackSaved = value;}
	void SetMainWeapon(AWeaponBase* value) {mMainWeapon = value;}
	void SetAttackCount(int32 value) {mAttackCount = value;}

	void SetIsDodge(bool value) {bIsDodge = value;}

	void SetTakeDamage(bool value) {bTakeDamage = value;}

	void IncreaseAttackCount();
	bool IsMainWeaponNull() const {return mMainWeapon == nullptr;}
	float GetMainWeaponAbilityValue() const;
};
