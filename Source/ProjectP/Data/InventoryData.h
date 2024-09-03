// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "UObject/NoExportTypes.h"
#include "InventoryData.generated.h"

namespace EEquipmentType
{
	enum Type : uint8
	{
		None = 0,
		Main,
		Sub,
		Armor,
		Potion,
	};
}

UCLASS()
class PROJECTP_API UInventoryData : public UObject
{
	GENERATED_BODY()

protected:
	TArray<FItem*> mMainItemArray;
	TArray<FItem*> mPotionItemArray;
	
	FItem* mMainItem = nullptr;
	FItem* mPotionItem = nullptr;

	uint32 mMainItemIndex = 0;
	uint32 mPotionItemIndex = 0;

	TObjectPtr<class AInGamePlayerController> mController = nullptr;

public:
	void SetItemMap(const UDataTable* dataTable, const TMap<FName, int32>& nameMap, TMap<FItem*, int32>& itemMap, bool firstItemIsNull = true);
	void SetItem(const UDataTable* dataTable, const TArray<FName>& nameArray, TArray<FItem*>& itemArray, bool firstItemIsNull = true);

	TArray<FItem*>& GetMainItemArray() {return mMainItemArray;}
	TArray<FItem*>& GetPotionItemArray() {return mPotionItemArray;}

	FItem* GetMainItem() const {return mMainItem;}
	FItem* GetPotionItem() const {return mPotionItem;}

	uint32 GetMainItemIndex() const {return mMainItemIndex;}
	uint32 GetPotionItemIndex() const {return mPotionItemIndex;}

	void SetMainItemIndex(uint32 value) {mMainItemIndex = value;}
	void SetPotionItemIndex(uint32 value) {mPotionItemIndex = value;}

	void SetMainItem(FItem* value) {mMainItem = value;}
	void SetPotionItem(FItem* value) {mPotionItem = value;}

	void SetNextItem(EEquipmentType::Type type);

	void InitInventoryWidget(const class APlayerControls* player);
};
