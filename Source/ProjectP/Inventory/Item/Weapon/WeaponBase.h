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
	TObjectPtr<AActor> mOwner = nullptr;

public:
	AWeaponBase();

private:
	bool bIsEquipped = false;

public:
	// getter
	FWeapon* GetWeaponData() const {return mWeaponData;}
	bool GetIsEquipped() const {return bIsEquipped;}

	// setter
	void SetSkeletalMesh(USkeletalMeshComponent* value) {mSkeletalMesh = value;}
	
	virtual void SetData(FItem* itemData, bool relocate) override;

	// interface
	virtual void SetOwner(AActor* actor) override;
	virtual void OnEquip() override;
	virtual void OnUnequip() override;

protected:
	// interface
	virtual void AttachActor(FName& socketName) override;
};