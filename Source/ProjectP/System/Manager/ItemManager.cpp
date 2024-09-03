// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManager.h"

CItemManager::CItemManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		itemTable(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Item.DT_Item'"));

	if(itemTable.Succeeded())
		mItemTable = itemTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable>
		weaponTable(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Weapon.DT_Weapon'"));

	if(weaponTable.Succeeded())
		mWeaponTable = weaponTable.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>
		swordTable(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Sword.DT_Sword'"));

	if(swordTable.Succeeded())
		mSwordTable = swordTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable>
		potionTable(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Potion.DT_Potion'"));

	if(potionTable.Succeeded())
		mPotionTable = potionTable.Object;
}

CItemManager::~CItemManager()
{
}