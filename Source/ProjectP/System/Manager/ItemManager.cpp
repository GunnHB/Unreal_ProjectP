// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

CItemManager::CItemManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		itemTable(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Item.DT_Item'"));

	if(itemTable.Succeeded())
		mItemTable = itemTable.Object;

	Initialize();
}

CItemManager::~CItemManager()
{
}

void CItemManager::Initialize()
{
	InitTable(mItemTable, mItemDataArray);
	InitTable(mWeaponTable, mWeaponDataArray);
	InitTable(mSwordTable, mSwordDataArray);

	SetWeaponMap();
	SetSwordMap();
}

void CItemManager::SetWeaponMap()
{
	for (int index = 0; index < mWeaponDataArray.Num(); ++index)
		mWeaponMap.Add(mWeaponDataArray[index]->id, mWeaponDataArray[index]);
}

void CItemManager::SetSwordMap()
{
	for (int index = 0; index < mSwordDataArray.Num(); ++index)
		mSwordMap.Add(mSwordDataArray[index]->id, mSwordDataArray[index]);
}

template <typename T>
void CItemManager::InitTable(UDataTable* table, TArray<T*>& array)
{
	if(!IsValid(table))
		return;
	
	table->GetAllRows<T>(TEXT(""), array);
	mTableArray.Add(table);
}
