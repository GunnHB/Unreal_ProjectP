// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePlayerController.h"

#include "../../Inventory/Widget/MainWidget.h"
#include "../../System/Manager/UIManager.h"
#include "../../Data/DataAsset/InventoryDataAsset.h"

AInGamePlayerController::AInGamePlayerController()
{
	static ConstructorHelpers::FObjectFinder<UDataAsset>
		invenDataAsset(TEXT("/Script/ProjectP.InventoryDataAsset'/Game/09_DataAsset/DA_Inventory.DA_Inventory'"));

	if(invenDataAsset.Succeeded())
		mDataAsset = Cast<UInventoryDataAsset>(invenDataAsset.Object);
}

void AInGamePlayerController::InitPlayerHealthBar(const float maxValue, const float currValue) const
{
	if(IsValid(CUIManager::GetInstance()->GetMainWidget()))
		CUIManager::GetInstance()->GetMainWidget()->InitPlayerHealthBar(maxValue, currValue);
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AInGamePlayerController::StartHPTimer(const uint8 value)
{
	mLoopCount = value / 5;
	
	GetWorld()->GetTimerManager().SetTimer(mHPTimer, this, &AInGamePlayerController::EndHPTimer, .05f, true);
}

void AInGamePlayerController::EndHPTimer()
{
	--mLoopCount;
	
	if(mLoopCount <= 0)
		GetWorld()->GetTimerManager().ClearTimer(mHPTimer);

	if(IsValid(CUIManager::GetInstance()->GetMainWidget()))
		CUIManager::GetInstance()->GetMainWidget()->SetPlayerCurrHealthBar(5);
}

void AInGamePlayerController::SetPlayerStamina(const float value, const bool isExhausted) const
{
	if(IsValid(CUIManager::GetInstance()->GetMainWidget()))
		CUIManager::GetInstance()->GetMainWidget()->SetPlayerStamina(value, isExhausted);
}

void AInGamePlayerController::SetInventoryData() const
{
	if(IsValid(mDataAsset) && IsValid(CUIManager::GetInstance()->GetMainWidget()))
		CUIManager::GetInstance()->GetMainWidget()->SetEquipmentWidget(mDataAsset);
 }
