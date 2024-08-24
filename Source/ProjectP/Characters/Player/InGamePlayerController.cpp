// Fill out your copyright notice in the Description page of Project Settings.

#include "InGamePlayerController.h"

#include "../../Inventory/Widget/MainWidget.h"

AInGamePlayerController::AInGamePlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>
		uiAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/03_UI/Widget/UI_Main.UI_Main_C'"));

	if(uiAsset.Succeeded())
		mMainWidgetClass = uiAsset.Class;
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(mMainWidgetClass))
	{
		if(!IsValid(mMainWidget))
		{
			mMainWidget = CreateWidget<UMainWidget>(GetWorld(), mMainWidgetClass);

			if(IsValid(mMainWidget))
				mMainWidget->AddToViewport();
		}
	}
}

void AInGamePlayerController::SetPlayerHP(const float value) const
{
	if(IsValid(mMainWidget))
		mMainWidget->SetPlayerHP(value);
}

void AInGamePlayerController::SetPlayerStamina(const float value) const
{
	if(IsValid(mMainWidget))
		mMainWidget->SetPlayerStamina(value);
}
