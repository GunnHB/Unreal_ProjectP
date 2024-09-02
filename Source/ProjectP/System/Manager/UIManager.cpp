// Fill out your copyright notice in the Description page of Project Settings.

#include "UIManager.h"

#include "../../Inventory/Widget/MainWidget.h"

CUIManager::CUIManager()
{
	static ConstructorHelpers::FClassFinder<UMainWidget>
		mainWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/03_UI/Widget/UI_Main.UI_Main_C'"));

	if(mainWidgetAsset.Succeeded())
		mMainWidgetClass = mainWidgetAsset.Class;
}

CUIManager::~CUIManager()
{

}

void CUIManager::InitWorld(UWorld* world)
{
	if(IsValid(world))
		mWorld = world;
}

UMainWidget* CUIManager::GetMainWidget()
{
	if(!IsValid(mMainWidget))
	{
		if(!IsValid(mMainWidgetClass) || !IsValid(mWorld))
			return nullptr;

		mMainWidget = CreateWidget<UMainWidget>(mWorld, mMainWidgetClass);

		if(IsValid(mMainWidget))
			mMainWidget->AddToViewport();
	}

	return mMainWidget;
}
