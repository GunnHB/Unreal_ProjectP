// Fill out your copyright notice in the Description page of Project Settings.


#include "HeartWidget.h"

void UHeartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mHeartImage = Cast<UImage>(GetWidgetFromName(GameValue::GetUIHeartImageFName()));

	if(IsValid(mHeartImage))
		SetHeart(EHeartType::Empty);
}

void UHeartWidget::SetHeart(EHeartType::Type type)
{
	float value = 0.f;
	
	switch (type)
	{
	case EHeartType::Empty:
		{
			value = 0.f;
			mHeartType = EHeartType::Empty;
		}
		break;
	case EHeartType::OneQuarter:
		{
			value = .25f;
			mHeartType = EHeartType::OneQuarter;
		}
		break;
	case EHeartType::Half:
		{
			value = .5f;
			mHeartType = EHeartType::Half;
		}
		break;
	case EHeartType::ThreeQuarter:
		{
			value = .75f;
			mHeartType = EHeartType::ThreeQuarter;
		}
		break;
	case EHeartType::Full:
		{
			value = 1.f;
			mHeartType = EHeartType::Full;
		}
		break;
	}
	
	if(IsValid(mHeartImage))
		mHeartImage->GetDynamicMaterial()->SetScalarParameterValue(GameValue::GetUIHeartMaterialScalarParamFName(), value);
}