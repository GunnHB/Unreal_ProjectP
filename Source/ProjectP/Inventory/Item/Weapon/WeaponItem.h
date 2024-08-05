// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../Interface/Equippable.h"

#include "../ItemBase.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AWeaponItem : public AItemBase, public IEquippable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<USkeletalMeshComponent> mSkeletalMesh;

	FWeapon* mWeaponData;
	bool isEquipped = false;

public:
	AWeaponItem();

	// interface
	virtual void OnEquip() override;
	virtual void OnUnequip() override;
	virtual void AttachActor(FName& socketName) override;

protected:
	// setter
	void SetWeaponData(FWeapon* data)
	{
		if(data != nullptr)
			mWeaponData = data;
	}
};
