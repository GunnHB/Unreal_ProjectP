// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "HeartWidget.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	mHealthBarWrapBox = Cast<UWrapBox>(GetWidgetFromName(GameValue::GetUIHealthBarWrapBoxFName()));
}

void UHealthBarWidget::SetHealthBar(const float value)
{
	if(IsValid(mHealthBarWrapBox))
	{
		float heartAmount = value / 20.f;

		for(int index = 0; index < heartAmount; ++index)
		{
			UHeartWidget* heartWidget = Cast<UHeartWidget>(CreateWidget(GetWorld(), mHeartWidgetClass));

			if(IsValid(heartWidget))
			{
				heartWidget->SetHeart(EHeartType::Full);
				mHealthBarWrapBox->AddChildToWrapBox(heartWidget);

				mHeartArray.Add(heartWidget);
			}
		}
	}
}

void UHealthBarWidget::SetCurrHP(const float value)
{
	if(mHeartArray.Num() > 0)
	{
		for (uint8 index = mHeartArray.Num(); index > 0; --index)
		{
			UHeartWidget* currHeart = mHeartArray[index - 1];

			if(currHeart->IsEmpty())
				continue;

			currHeart->SetHeart(static_cast<EHeartType::Type>(value));
		}
	}
}
