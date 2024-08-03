// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"
#include "ProjectP/System/GameInfo.h"

class PROJECTP_API CItemManager : public CBaseManager<CItemManager>
{
public:
	CItemManager();
	~CItemManager();

protected:
	TArray<UDataTable*> mTableArray;
	TObjectPtr<UDataTable> mItemTable = nullptr;
	TObjectPtr<UDataTable> mWeaponTable = nullptr;
	TObjectPtr<UDataTable> mSwordTable = nullptr;

public:
	TArray<FItem*> mItemDataArray;
	TArray<FWeapon*> mWeaponDataArray;
	TArray<FSword*> mSwordDataArray;

	template <typename T>
	T* GetData(const FName& name)
	{
		for (int32 index = 0; index < mTableArray.Num(); ++index)
		{
			UDataTable* tempTable = mTableArray[index];
			T* tempData = tempTable->FindRow<T>(name, "");
			
			if(tempData == nullptr)
				continue;
			else
				return tempData;
		}

		return nullptr;
	}

private:
	void Initialize();
	
	template <typename T>
	void InitTable(UDataTable* table, TArray<T*>& array);
};
