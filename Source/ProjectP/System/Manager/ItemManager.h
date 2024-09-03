// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"

class PROJECTP_API CItemManager : public CBaseManager<CItemManager>
{
public:
	CItemManager();
	~CItemManager();

protected:
	TObjectPtr<UDataTable> mItemTable = nullptr;
	TObjectPtr<UDataTable> mWeaponTable = nullptr;
	TObjectPtr<UDataTable> mSwordTable = nullptr;
	TObjectPtr<UDataTable> mPotionTable = nullptr;

public:
	UDataTable* GetItemTable() const {return mItemTable;}
	UDataTable* GetWeaponTable() const {return mWeaponTable;}
	UDataTable* GetSwordTable() const {return mSwordTable;}
	UDataTable* GetPotionTable() const {return mPotionTable;}
};