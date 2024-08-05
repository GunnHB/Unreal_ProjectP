// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponItem.h"
#include "SwordItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ASwordItem : public AWeaponItem
{
	GENERATED_BODY()

protected:
	FSword* mSwordData;

public:
	ASwordItem();
	
	void SetData(FSword* data);

protected:
	virtual void BeginPlay() override;
};
