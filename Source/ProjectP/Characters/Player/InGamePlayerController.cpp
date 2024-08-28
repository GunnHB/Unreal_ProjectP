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

void AInGamePlayerController::StartHPTimer(const float damage)
{
	mLoopCount = (uint8)damage / 5;
	
	GetWorld()->GetTimerManager().SetTimer(mHPTimer, this, &AInGamePlayerController::EndHPTimer, .2f, true);
}

void AInGamePlayerController::EndHPTimer()
{
	--mLoopCount;
	
	if(mLoopCount <= 0)
		GetWorld()->GetTimerManager().ClearTimer(mHPTimer);
	
	UE_LOG(ProjectP, Warning, TEXT("asdfasdf"));
	
	if(IsValid(mMainWidget))
		mMainWidget->SetPlayerCurrHP(mLoopCount);
}

void AInGamePlayerController::SetPlayerMaxHP(const float value) const
{
	if(IsValid(mMainWidget))
		mMainWidget->SetPlayerMaxHP(value);
}

void AInGamePlayerController::SetPlayerStamina(const float value, const bool isExhausted) const
{
	if(IsValid(mMainWidget))
		mMainWidget->SetPlayerStamina(value, isExhausted);
}

void AInGamePlayerController::SetPlayerCurrHP(const float value)
{
	StartHPTimer(value);
}
