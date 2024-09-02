// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "EnemyHealthBarWidget.h"
#include "EquipmentWidget.h"
#include "HealthBarWidget.h"
#include "StaminaWidget.h"
#include "EnemyHealthBarWidget.h"

#include "../../Data/EnemyStat.h"

#include "../../Data/InventoryData.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	mHealthBarWidget = Cast<UHealthBarWidget>(GetWidgetFromName(GameValue::GetUIHealthBarFName()));
	mStaminaWidget = Cast<UStaminaWidget>(GetWidgetFromName(GameValue::GetUIStaminaFName()));
	mEquipmentWidget = Cast<UEquipmentWidget>(GetWidgetFromName(GameValue::GetUIEquipmentFName()));
	mEnemyHPWidget = Cast<UEnemyHealthBarWidget>(GetWidgetFromName(GameValue::GetUIEnemyStatFName()));

	if(IsValid(mStaminaWidget))
		mStaminaWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainWidget::InitPlayerHealthBar(const float maxValue, const float currValue) const
{
	if(IsValid(mHealthBarWidget))
		mHealthBarWidget->InitHealthBar(maxValue, currValue);
}

void UMainWidget::InitEnemyHealthBar(class UEnemyStat* enemyStat) const
{
	if(IsValid(enemyStat))
		mEnemyHPWidget->SetEnemyHP(enemyStat);
}

void UMainWidget::SetPlayerStamina(const float value, const bool isExhausted) const
{
	if(IsValid(mStaminaWidget))
	{
		mStaminaWidget->SetStamina(value);
		mStaminaWidget->SetVisibility(value < 1.f ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);

		mStaminaWidget->SetExhaust(isExhausted);
	}
}

// void UMainWidget::SetEquipmentWidget(const UInventoryDataAsset* dataAsset) const
// {
// 	// if(dataAsset->GetMainItemArray().Num() > 0)
// 	// 	mEquipmentWidget->InitMainItem(dataAsset->GetMainItemArray()[0]);
// }

void UMainWidget::SetEquipmentWidget(UInventoryData* data) const
{
	if(IsValid(data))
		SetMainEquipmentWidget(data->GetMainItemArray()[0]);
}

void UMainWidget::SetMainEquipmentWidget(const FItem* item) const
{
	mEquipmentWidget->SetMainItem(item);
}

void UMainWidget::SetPlayerCurrHealthBar(const float damageValue)
{
	if(IsValid(mHealthBarWidget))
		mHealthBarWidget->SetCurrHealthBar(damageValue);
}

void UMainWidget::ActiveEnemyHP(bool active) const
{
	if(IsValid(mEnemyHPWidget))
		mEnemyHPWidget->SetVisibility(active ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}
