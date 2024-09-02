// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryData.h"

#include "../Characters/Player/PlayerControls.h"
#include "../Characters/Player/InGamePlayerController.h"

void UInventoryData::InitInventoryWidget(const APlayerControls* player)
{
	if(IsValid(player))
	{
		AInGamePlayerController* playerController = Cast<AInGamePlayerController>(player->GetController());

		if(IsValid(playerController))
			playerController->SetInventoryData(this);
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
