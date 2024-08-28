// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"

#include "Engine/DataAsset.h"
#include "InventoryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UInventoryDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere) TArray<FName> mMainItemRowNameArray;
	UPROPERTY(EditAnywhere) TArray<FName> mSubItemRowNameArray;
	UPROPERTY(EditAnywhere) TArray<FName> mArmorItemRowNameArray;
	UPROPERTY(EditAnywhere) TArray<FName> mPotionItemRowNameArray;

public:
	TArray<FName> GetMainItemRowNameArray() const {return mMainItemRowNameArray;}
};
