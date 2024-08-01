// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../EquipmentItem.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AWeaponItem : public AEquipmentItem
{
	GENERATED_BODY()

protected:
	FWeapon* mWeaponData;

public:
	AWeaponItem();
};
