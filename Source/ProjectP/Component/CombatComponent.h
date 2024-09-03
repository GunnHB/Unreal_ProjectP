// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "Components/ActorComponent.h"
#include "ProjectP/Inventory/Item/Weapon/WeaponBase.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	TObjectPtr<class AWeaponBase> mMainWeapon = nullptr;
	TObjectPtr<class AWeaponBase> mSubWeapon = nullptr;

	// attack
	bool bIsCombatEnable = false;
	bool bIsAttackSaved = false;
	bool bIsRandomAttack = false;
	bool bIsKnockBack = false;
	uint8 mKnockBackCallCount = 0;
	
	int32 mAttackIndex = 0;

	FTimerHandle mInterpTimeHandle;
	FVector mKnockBackDirection = FVector::ZeroVector;

public:	
	// getter
	bool GetCombatEnable() const {return bIsCombatEnable;}
	bool GetIsAttackSaved() const {return bIsAttackSaved;}
	AWeaponBase* GetMainWeapon() const {return mMainWeapon;}
	AWeaponBase* GetSubWeapon() const {return mSubWeapon;}
	int32 GetAttackIndex() const {return mAttackIndex;}
	bool GetIsKnockBack() const {return bIsKnockBack;}
	
	// setter
	void SetCombatEnable(bool value) {bIsCombatEnable = value;}
	void SetIsAttackSaved(bool value) {bIsAttackSaved = value;}
	void SetMainWeapon(AWeaponBase* value) {mMainWeapon = value;}
	void SetSubWeapon(AWeaponBase* value) {mSubWeapon = value;}
	void SetAttackIndex(int32 value) {mAttackIndex = value;}
	void SetIsRandomAttack(bool value) {bIsRandomAttack = value;}

	void IncreaseAttackCount();
	bool IsMainWeaponNull() const {return mMainWeapon == nullptr;}
	float GetMainWeaponAbilityValue() const;
	
	class UCollisionComponent* GetMainCollisionComp() const;

	void KnockBack(const AActor* hitter);
	void EnableRagdoll(USkeletalMeshComponent* mesh, UCapsuleComponent* capsule) const;
	
	void InterpActorLocation();

	void PerformAttack(class UAnimInstanceBase* animInstance);
	void PerformAttack(class UAnimInstanceBase* animInstance, const TArray<UAnimMontage*>& attackMontageArray);

	void SetItem(FItem* item);
};
