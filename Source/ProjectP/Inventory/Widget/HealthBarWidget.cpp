// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "HeartWidget.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	mHealthBarWrapBox = Cast<UWrapBox>(GetWidgetFromName(GameValue::GetUIHealthBarWrapBoxFName()));
}

void UHealthBarWidget::InitHealthBar(const float maxHP, const float currHP)
{
	uint8 heartCount = maxHP / 20;
	int8 heartValue = currHP / heartCount;

	if(IsValid(mHeartWidgetClass))
	{
		for (uint8 index = 0; index < heartCount; ++index)
		{
			UHeartWidget* heartWidget = Cast<UHeartWidget>(CreateWidget(GetWorld(), mHeartWidgetClass));

			if(IsValid(heartWidget))
			{
				if(IsValid(mHealthBarWrapBox))
					mHealthBarWrapBox->AddChild(heartWidget);

				if(heartValue >= 4)
					heartWidget->SetHeart(EHeartType::Full);
				else
					heartWidget->SetHeart(static_cast<EHeartType::Type>(heartValue));

				mHeartArray.Add(heartWidget);

				// 마지막으로 채워진 체력으로 갱신
				if(!heartWidget->IsEmpty())
					mLastIndex = index;

				heartValue -= 4;

				if(heartValue < 0)
					heartValue = 0;
			}
		}
	}
}

// value는 증감량
void UHealthBarWidget::SetCurrHealthBar(const float value)
{
	if(mHeartArray[mLastIndex]->IsEmpty())
		--mLastIndex;

	mLastIndex = mLastIndex < 0 ? 0 : mLastIndex;

	int8 heartValue = (mHeartArray[mLastIndex]->GetHeartType() - 1) < 0 ? 0 : mHeartArray[mLastIndex]->GetHeartType() - 1;
	
	mHeartArray[mLastIndex]->SetHeart(static_cast<EHeartType::Type>(heartValue));
}