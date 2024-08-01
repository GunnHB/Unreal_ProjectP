// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "../Characters/Player/PlayerControls.h"

#include "Manager/ItemManager.h"

AMainGameMode::AMainGameMode()
{
	DefaultPawnClass = APlayerControls::StaticClass();

	CItemManager::GetInstance()->Init();
}