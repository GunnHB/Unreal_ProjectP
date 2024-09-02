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
	TArray<FItem*> mMainItemArray;
	TArray<FItem*> mPotionItemArray;

public:
	void SetItemArray(const UDataTable* dataTable, const TArray<FName>& nameArray, TArray<FItem*>& itemArray);

	TArray<FItem*>& GetMainItemArray() {return mMainItemArray;}
	TArray<FItem*>& GetPotionItemArray() {return mPotionItemArray;}

	void InitInventoryWidget(const class APlayerControls* player);
};
