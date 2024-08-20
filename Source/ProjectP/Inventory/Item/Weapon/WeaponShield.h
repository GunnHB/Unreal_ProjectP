// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"

#include "WeaponBase.h"
#include "WeaponShield.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AWeaponShield : public AWeaponBase
{
	GENERATED_BODY()

public:
	AWeaponShield();

	virtual void SetData(FItem* itemData, bool relocate) override;
};
