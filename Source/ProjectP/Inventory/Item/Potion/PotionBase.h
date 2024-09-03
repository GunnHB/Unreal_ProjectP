// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"

#include "../ItemBase.h"
#include "PotionBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APotionBase : public AItemBase
{
	GENERATED_BODY()

public:
	APotionBase();

protected:
	FPotion* mPotionData;

public:
	FPotion* GetPotionData() const {return mPotionData;}

	virtual void SetData(FItem* itemData, bool relocate) override;
};
