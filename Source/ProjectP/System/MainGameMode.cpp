// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "../Characters/Player/PlayerControls.h"
#include "../Characters/Player/InGamePlayerController.h"

#include "Manager/ItemManager.h"
#include "Manager/UIManager.h"

AMainGameMode::AMainGameMode()
{
	DefaultPawnClass = APlayerControls::StaticClass();
	PlayerControllerClass = AInGamePlayerController::StaticClass();

	CItemManager::GetInstance()->Init();
	CUIManager::GetInstance()->Init();
	CUIManager::GetInstance()->InitWorld(GetWorld());
}

AMainGameMode::~AMainGameMode()
{
	CItemManager::DestroyInstance();
	CUIManager::DestroyInstance();
}
