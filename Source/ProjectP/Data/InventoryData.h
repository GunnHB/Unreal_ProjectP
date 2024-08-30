// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "UObject/NoExportTypes.h"
#include "InventoryData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UInventoryData : public UObject
{
	GENERATED_BODY()

protected:
	TArray<FItem> mMainItemArray;

public:
	void InitInventory(const class APlayerControls* player);
};
