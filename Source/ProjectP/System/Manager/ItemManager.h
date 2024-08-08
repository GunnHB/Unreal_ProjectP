// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"
#include "ProjectP/System/GameInfo.h"

class PROJECTP_API CItemManager : public CBaseManager<CItemManager>
{
public:
	CItemManager();
	~CItemManager();
	
	TObjectPtr<UDataTable> mItemTable = nullptr;
	TObjectPtr<UDataTable> mWeaponTable = nullptr;
	TObjectPtr<UDataTable> mSwordTable = nullptr;
};