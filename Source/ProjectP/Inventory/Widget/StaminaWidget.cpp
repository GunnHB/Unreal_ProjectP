// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaWidget.h"

void UStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStaminaImage = Cast<UImage>(GetWidgetFromName(GameValue::GetUIStaminaImageFName()));
}

void UStaminaWidget::SetStamina(const float value) const
{
}
