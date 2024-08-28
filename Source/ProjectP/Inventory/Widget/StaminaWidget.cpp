// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaWidget.h"

void UStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStaminaImage = Cast<UImage>(GetWidgetFromName(GameValue::GetUIStaminaImageFName()));
}

void UStaminaWidget::SetStamina(const float value) const
{
	if(IsValid(mStaminaImage))
		mStaminaImage->GetDynamicMaterial()->SetScalarParameterValue(GameValue::GetUIStaminaMaterialScalarParamFName(), value);
}

void UStaminaWidget::SetExhaust(const bool isExhaust) const
{
	mStaminaImage->GetDynamicMaterial()->SetVectorParameterValue(GameValue::GetUIStaminaMaterialColorParamFName(), isExhaust ? FColor::Red : FColor::Green);
}
