// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePlayerController.h"

#include "../../Inventory/Widget/MainWidget.h"
#include "../../Inventory/Widget/EquipmentWidget.h"
#include "../../System/Manager/UIManager.h"

#include "../../Data/DataAsset/InventoryDataAsset.h"
#include "../../Data/InventoryData.h"

AInGamePlayerController::AInGamePlayerController()
{
	static ConstructorHelpers::FObjectFinder<UDataAsset>
		invenDataAsset(TEXT("/Script/ProjectP.InventoryDataAsset'/Game/09_DataAsset/DA_Inventory.DA_Inventory'"));

	if(invenDataAsset.Succeeded())
	{
		mDataAsset = Cast<UInventoryDataAsset>(invenDataAsset.Object);

		if(IsValid(mDataAsset))
		{
			static ConstructorHelpers::FObjectFinder<UDataTable>
				dataTableAsset(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Item.DT_Item'"));

			if(dataTableAsset.Succeeded())
				mDataAsset->SetDataTable(dataTableAsset.Object);
		}
	}
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

void AInGamePlayerController::RefreshItemSlotWidget(const FItem* item)
{
	UMainWidget* mainWidget = CUIManager::GetInstance()->GetMainWidget();

	if(!IsValid(mainWidget))
	{
		UE_LOG(ProjectP, Warning, TEXT("no main widget!!"));
		return;
	}

	UEquipmentWidget* equipmentWidget = mainWidget->GetEquipmentWidget();

	if(!IsValid(equipmentWidget))
	{
		UE_LOG(ProjectP, Warning, TEXT("no equipment widget!!"));
		return;
	}

	if(item == nullptr)
	{
		equipmentWidget->SetMainItem(nullptr);
		return;	
	}
	
	if(item->type == EItemType::Weapon)
		equipmentWidget->SetMainItem(item);
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

void AInGamePlayerController::SetInventoryData(UInventoryData* data) const
{
	if(IsValid(data) && IsValid(CUIManager::GetInstance()->GetMainWidget()))
		CUIManager::GetInstance()->GetMainWidget()->SetEquipmentWidget(data);
}
