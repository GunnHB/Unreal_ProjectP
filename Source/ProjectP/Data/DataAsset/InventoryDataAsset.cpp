// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDataAsset.h"

void UInventoryDataAsset::SetFItemByFNameArray(const TArray<FName>& rowNameArray, TArray<FItem*>& itemArray) const
{
	if(!IsValid(mDataTable))
		return;
	
	if(rowNameArray.Num() > 0)
	{
		itemArray.Empty();
		
		for (FName rowName : rowNameArray)
		{
			FItem* item = mDataTable->FindRow<FItem>(rowName, "");

			if(item != nullptr)
				itemArray.Add(item);
		}
	}
}

void UInventoryDataAsset::SetDataTable(UDataTable* dataTable)
{
	if(IsValid(dataTable))
		mDataTable = dataTable;

	SetFItemByFNameArray(mMainItemRowNameArray, mMainItemArray);
}
