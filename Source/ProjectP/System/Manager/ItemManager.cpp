// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

CItemManager::CItemManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		weaponTableAsset(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Weapon.DT_Weapon'"));

	if(weaponTableAsset.Succeeded())
		mWeaponTable = weaponTableAsset.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>
		swordTableAsset(TEXT(""));

	if(swordTableAsset.Succeeded())
		mSwordTable = swordTableAsset.Object;

	Initialize();
}

CItemManager::~CItemManager()
{
}

template <typename T>
T* CItemManager::GetData(const FName& rowName)
{
	return nullptr;
}

template <typename T>
void CItemManager::InitTable(UDataTable* table, TArray<T*>& array)
{
	if(!IsValid(table))
		return;
	
	table->GetAllRows<T>(TEXT(""), array);
	mTableArray.Add(table);
}

void CItemManager::Initialize()
{
	InitTable(mWeaponTable, mWeaponDataArray);
	// InitTable(mSwordTable, mSwordDataArray);
}

void CItemManager::GetTargetTable()
{
	
}
