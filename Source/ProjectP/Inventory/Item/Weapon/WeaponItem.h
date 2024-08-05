// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ItemBase.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AWeaponItem : public AItemBase
{
	GENERATED_BODY()

protected:
	FWeapon* mWeaponData;

public:
	AWeaponItem();

protected:
	// setter
	void SetWeaponData(FWeapon* data)
	{
		if(data != nullptr)
			mWeaponData = data;
	}
};
