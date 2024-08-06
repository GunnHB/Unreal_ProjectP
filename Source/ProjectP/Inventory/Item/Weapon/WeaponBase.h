// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../Interface/Equippable.h"

#include "../ItemBase.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AWeaponBase : public AItemBase, public IEquippable
{
	GENERATED_BODY()

protected:
	TObjectPtr<USkeletalMeshComponent> mSkeletalMesh = nullptr;
	
	FWeapon* mWeaponData = nullptr;

public:
	AWeaponBase();

private:
	bool bIsEquipped = false;

public:
	// getter
	bool GetIsEquipped() const {return bIsEquipped;}

	// setter
	void SetSkeletalMesh(USkeletalMeshComponent* value) {mSkeletalMesh = value;}
	
	virtual void OnEquip() override;
	virtual void OnUnequip() override;

	virtual void SetData(FItem* itemData, bool relocate) override;
	
protected:
	virtual void AttachActor(FName& socketName) override;
};