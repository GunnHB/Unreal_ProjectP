// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "EquipmentWidget.h"
#include "HealthBarWidget.h"
#include "StaminaWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	mHealthBarWidget = Cast<UHealthBarWidget>(GetWidgetFromName(GameValue::GetUIHealthBarFName()));
	mStaminaWidget = Cast<UStaminaWidget>(GetWidgetFromName(GameValue::GetUIStaminaFName()));
	mEquipmentWidget = Cast<UEquipmentWidget>(GetWidgetFromName(GameValue::GetUIEquipmentFName()));

	if(IsValid(mStaminaWidget))
		mStaminaWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainWidget::InitPlayerHealthBar(const float maxValue, const float currValue) const
{
	if(IsValid(mHealthBarWidget))
		mHealthBarWidget->InitHealthBar(maxValue, currValue);
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

void UMainWidget::SetEquipmentWidget()
{
}

void UMainWidget::SetPlayerCurrHealthBar(const float damageValue)
{
	if(IsValid(mHealthBarWidget))
		mHealthBarWidget->SetCurrHealthBar(damageValue);
}
