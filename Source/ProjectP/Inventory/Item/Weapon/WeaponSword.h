// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponBase.h"
#include "WeaponSword.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AWeaponSword : public AWeaponBase
{
	GENERATED_BODY()

protected:
	FSword* mSwordData = nullptr;

public:
	AWeaponSword();

	FSword* GetSwordData() const {return mSwordData;}
	
	virtual void SetData(FItem* itemData, bool relocate) override;
	
	void ResetTransform();
};
