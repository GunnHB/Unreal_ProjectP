// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"

class PROJECTP_API CItemManager : public CBaseManager<CItemManager>
{
public:
	CItemManager();
	~CItemManager();

protected:
	TArray<UDataTable*> mTableArray;
	TObjectPtr<UDataTable> mWeaponTable = nullptr;
	TObjectPtr<UDataTable> mSwordTable = nullptr;

public:
	TArray<FWeapon*> mWeaponDataArray;
	TArray<FSword*> mSwordDataArray;

	template <typename T>
	T* GetData(const FName& rowName);

private:
	void Initialize();
	void GetTargetTable();
	
	template <typename T>
	void InitTable(UDataTable* table, TArray<T*>& array);
};
