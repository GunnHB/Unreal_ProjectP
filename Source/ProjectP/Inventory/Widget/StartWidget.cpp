// Fill out your copyright notice in the Description page of Project Settings.

#include "StartWidget.h"

#include "../../Characters/Player/InGamePlayerController.h"

void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mStartButton = Cast<UButton>(GetWidgetFromName(GameValue::GetUIStartButtonFName()));

	if(IsValid(mStartButton))
		mStartButton->OnClicked.AddDynamic(this, &UStartWidget::OnClickStartButton);
}

void UStartWidget::OnClickStartButton()
{
	AInGamePlayerController* controller = Cast<AInGamePlayerController>(GetOwningPlayer());

	if(IsValid(controller))
		controller->SetGameOnly(this);
}
