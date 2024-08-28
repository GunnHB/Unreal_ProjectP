// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "HeartWidget.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	mHealthBarWrapBox = Cast<UWrapBox>(GetWidgetFromName(GameValue::GetUIHealthBarWrapBoxFName()));
}

void UHealthBarWidget::SetMaxHealthBar(const float maxHP)
{
	uint8 heartCount = maxHP / 20;

	if(IsValid(mHeartWidgetClass))
	{
		for (uint8 index = 0; index < heartCount; ++index)
		{
			UHeartWidget* heartWidget = Cast<UHeartWidget>(CreateWidget(GetWorld(), mHeartWidgetClass));

			if(IsValid(heartWidget))
			{
				if(IsValid(mHealthBarWrapBox))
					mHealthBarWrapBox->AddChild(heartWidget);
				
				mHeartArray.Add(heartWidget);
				heartWidget->SetHeart(EHeartType::Empty);
			}
		}
	}
}
