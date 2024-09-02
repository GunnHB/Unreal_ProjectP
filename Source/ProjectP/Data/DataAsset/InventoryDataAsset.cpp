// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryDataAsset.h"

void UInventoryDataAsset::SetDataTable(UDataTable* dataTable)
{
	if(IsValid(dataTable))
		mDataTable = dataTable;
}
