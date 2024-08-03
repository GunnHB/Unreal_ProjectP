// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

CItemManager::CItemManager()
{
	// static ConstructorHelpers::FObjectFinder<UDataTable>
	// 	weaponTableAsset(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Weapon.DT_Weapon'"));
	//
	// if(weaponTableAsset.Succeeded())
	// 	mWeaponTable = weaponTableAsset.Object;
	//
	// static ConstructorHelpers::FObjectFinder<UDataTable>
	// 	swordTableAsset(TEXT(""));
	//
	// if(swordTableAsset.Succeeded())
	// 	mSwordTable = swordTableAsset.Object;

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
	// InitTable(mWeaponTable, mWeaponDataArray);
	InitTable(mItemTable, mItemDataArray);
}

template <typename T>
void CItemManager::InitTable(UDataTable* table, TArray<T*>& array)
{
	if(!IsValid(table))
		return;
	
	table->GetAllRows<T>(TEXT(""), array);
	mTableArray.Add(table);
}