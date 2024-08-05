// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	TObjectPtr<class AWeaponBase> mMainWeapon = nullptr;

	bool bIsCombatEnable = false;

	int32 mAttackCount = 0;
	bool bIsAttackSaved = false;
	bool bIsAttacking = false;

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	
	// getter
	AWeaponBase* GetMainWeapon() const {return mMainWeapon;}
	bool GetCombatEnable() const {return bIsCombatEnable;}
	bool GetIsAttacking() const {return bIsAttacking;}
	bool GetIsAttackSaved() const {return bIsAttackSaved;}
	
	// setter
	void SetMainWeapon(AWeaponBase* value) {mMainWeapon = value;}
	void SetCombatEnable(bool value) {bIsCombatEnable = value;}
	void SetIsAttacking(bool value) {bIsAttacking = value;}
	void SetIsAttackSaved(bool value) {bIsAttackSaved = value;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
