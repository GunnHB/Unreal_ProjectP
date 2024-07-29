// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "../../Characters/Player/PlayerControls.h"
#include "ProjectP/Data/Player/PlayerData.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitWidget();
	InitAssets();

	SetMoneyText();
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::I)
	{
		FInputModeGameOnly gameOnlyMode;
		SetMode(gameOnlyMode, false);

		RemoveFromParent();
	}
	
	return result;
}

void UInventoryWidget::InitWidget()
{
	SetIsFocusable(true);							// 포커스 가능 여부
	SetKeyboardFocus();								// 키보드 입력 받기
	
	FInputModeUIOnly uiOnlyMode;					// ui 전용
	SetMode(uiOnlyMode, true);
}

void UInventoryWidget::InitAssets()
{
	if(mMoneyText == nullptr)
		mMoneyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Money")));
}

void UInventoryWidget::SetMoneyText()
{
	if (mMoneyText == nullptr)
		return;

	APlayerControls* player = Cast<APlayerControls>(GetOwnerPlayerPawn());

	if(!IsValid(player))
		return;

	mMoneyText->SetText(FText::FromString(FString::Printf(TEXT("%d"), player->GetThisPlayerData()->GetPlayerMoney())));
}

void UInventoryWidget::SetMode(const FInputModeDataBase& mode, bool showCursor)
{
	APlayerController* controller = GetOwningPlayer();
	
	if(!IsValid(controller))
		return;

	controller->SetInputMode(mode);
	controller->SetShowMouseCursor(showCursor);
}
