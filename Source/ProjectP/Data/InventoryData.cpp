// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryData.h"

#include "../Characters/Player/PlayerControls.h"
#include "../Characters/Player/InGamePlayerController.h"

#include "../System/Manager/UIManager.h"

void UInventoryData::UpdatePotionItemMap(const FItem* item, uint32 value)
{
	if(mPotionItemMap.Contains(item))
		mPotionItemMap[item] = value;
}

void UInventoryData::SetNextItem(EEquipmentType::Type type)
{
	if(!IsValid(mController))
		return;
	
	switch(type)
	{
	case EEquipmentType::Main:
		{
			++mMainItemIndex;

			// signed와 unsigned의 비교에서 에러가 발생해 캐스팅
			if(mMainItemIndex >= static_cast<uint32>(mMainItemArray.Num()))
				mMainItemIndex = 0;

			SetMainItem(mMainItemArray[mMainItemIndex]);
			mController->RefreshItemSlotWidget(GetMainItem(), type, this);
		}
		break;

	case EEquipmentType::Potion:
		{
			++mPotionItemIndex;

			if(mPotionItemIndex >= static_cast<uint32>(mPotionItemArray.Num()))
				mPotionItemIndex = 0;

			SetPotionItem(mPotionItemArray[mPotionItemIndex]);
			mController->RefreshItemSlotWidget(GetPotionItem(), type, this);
		}
	}
}

void UInventoryData::InitInventoryWidget(const APlayerControls* player)
{
	if(IsValid(player))
	{
		AInGamePlayerController* playerController = Cast<AInGamePlayerController>(player->GetController());

		if(IsValid(playerController))
		{
			mController = playerController;
			playerController->SetInventoryData(this);
		}
	}
}

void UInventoryData::SetItem(const UDataTable* dataTable, const TArray<FName>& nameArray, TArray<FItem*>& itemArray, bool firstItemIsNull)
{
	if(!IsValid(dataTable))
		return;

	if(nameArray.Num() > 0)
	{
		itemArray.Empty();

		if(firstItemIsNull)
			itemArray.Add(nullptr);

		for (FName name : nameArray)
		{
			FItem* item = dataTable->FindRow<FItem>(name, "");

			if(item != nullptr)
				itemArray.Add(item);

			if(item->type == EItemType::Consumption)
				mPotionItemMap.Add(item, 5);
		}
	}
}