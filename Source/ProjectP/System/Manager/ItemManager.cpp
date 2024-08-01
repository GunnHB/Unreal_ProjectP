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

// template <typename T>
// T* CItemManager::GetData()
// {
// 	for (int32 index = 0; index < mTableArray.Num(); ++index)
// 	{
// 		UDataTable* temp = mTableArray[index];
//
// 		if(temp->GetRowStruct() == typeid(T))
// 			UE_LOG(ProjectP, Warning, TEXT("sdfasdfsadfsdaf"));
// 	}
// 	
// 	return nullptr;
// }

void CItemManager::Initialize()
{
	InitTable(mWeaponTable, mWeaponDataArray);
}

template <typename T>
void CItemManager::InitTable(UDataTable* table, TArray<T*>& array)
{
	if(!IsValid(table))
		return;
	
	table->GetAllRows<T>(TEXT(""), array);
	mTableArray.Add(table);
}