// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryData.h"

#include "../Characters/Player/PlayerControls.h"
#include "../Characters/Player/InGamePlayerController.h"

void UInventoryData::SetNextItem(EEquipmentType::Type type)
{
	switch(type)
	{
	case EEquipmentType::Main:
		{
			++mMainItemIndex;

			// signed와 unsigned의 비교에서 에러가 발생해 캐스팅
			if(mMainItemIndex >= static_cast<uint32>(mMainItemArray.Num() - 1))
				mMainItemIndex = 0;

			mMainItem = mMainItemArray[mMainItemIndex];

			RefreshWidget(EEquipmentType::Main);
		}
		break;
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

void UInventoryData::RefreshWidget(EEquipmentType::Type type)
{
	if(!IsValid(mController))
		return;
	
	switch (type)
	{
	case EEquipmentType::Main:
		break;
	}
}

void UInventoryData::SetItemArray(const UDataTable* dataTable, const TArray<FName>& nameArray, TArray<FItem*>& itemArray)
{
	if(!IsValid(dataTable))
		return;

	if(nameArray.Num() > 0)
	{
		itemArray.Empty();

		// 빈 슬롯을 위한 공갈 데이터
		itemArray.Add(nullptr);
		
		for (FName name : nameArray)
		{
			FItem* item = dataTable->FindRow<FItem>(name, "");

			if(item != nullptr)
				itemArray.Add(item);
		}
	}
}
