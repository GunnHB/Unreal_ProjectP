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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment") TArray<FName> mMainItemRowNameArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment") TArray<FName> mSubItemRowNameArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment") TArray<FName> mArmorItemRowNameArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment") TArray<FName> mPotionItemRowNameArray;

	TArray<FItem*> mMainItemArray;
	TArray<FItem*> mSubItemArray;
	TArray<FItem*> mArmorItemArray;
	TArray<FItem*> mPotionItemArray;

	TObjectPtr<UDataTable> mDataTable = nullptr;
	
	void SetFItemByFNameArray(const TArray<FName>& rowNameArray, TArray<FItem*>& itemArray) const;

public:
	void SetDataTable(UDataTable* dataTable);
	TArray<FItem*> GetMainItemArray() const {return mMainItemArray;}
};
