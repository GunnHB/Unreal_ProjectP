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

	TObjectPtr<UDataTable> mDataTable = nullptr;

public:
	void SetDataTable(UDataTable* dataTable);

	TArray<FName> GetMainItemRowNameArray() const {return mMainItemRowNameArray;}
	TArray<FName> GetSubItemRowNameArray() const {return mSubItemRowNameArray;}
	TArray<FName> GetArmorItemRowNameArray() const {return mArmorItemRowNameArray;}
	TArray<FName> GetPotionItemRowNameArray() const {return mPotionItemRowNameArray;}

	UDataTable* GetDataTable() const {return mDataTable;}
};
