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

void AInGamePlayerController::InitPlayerHealthBar(const float maxValue, const float currValue) const
{
	if(IsValid(mMainWidget))
		mMainWidget->InitPlayerHealthBar(maxValue, currValue);
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

void AInGamePlayerController::StartHPTimer(const uint8 value)
{
	mLoopCount = value / 5;
	
	GetWorld()->GetTimerManager().SetTimer(mHPTimer, this, &AInGamePlayerController::EndHPTimer, .05f, true);
}

void AInGamePlayerController::EndHPTimer()
{
	--mLoopCount;
	
	if(mLoopCount <= 0)
		GetWorld()->GetTimerManager().ClearTimer(mHPTimer);
	
	if(IsValid(mMainWidget))
		mMainWidget->SetPlayerCurrHealthBar(5);
}

void AInGamePlayerController::SetPlayerStamina(const float value, const bool isExhausted) const
{
	if(IsValid(mMainWidget))
		mMainWidget->SetPlayerStamina(value, isExhausted);
}
