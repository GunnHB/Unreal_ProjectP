// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "HealthBarWidget.h"
#include "StaminaWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	mHealthBarWidget = Cast<UHealthBarWidget>(GetWidgetFromName(GameValue::GetUIHealthBarFName()));
	mStaminaWidget = Cast<UStaminaWidget>(GetWidgetFromName(GameValue::GetUIStaminaFName()));

	if(IsValid(mStaminaWidget))
		mStaminaWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainWidget::SetPlayerHP(const float value) const
{
	if(IsValid(mHealthBarWidget))
		mHealthBarWidget->SetHealthBar(value);
}

void UMainWidget::SetPlayerStamina(const float value) const
{
	if(IsValid(mStaminaWidget))
		mStaminaWidget->SetStamina(value);
}
