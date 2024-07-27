// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::I)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("input?")));

		FInputModeGameOnly mode;
		APlayerController* controller = GetOwningPlayer<APlayerController>();

		controller->SetInputMode(mode);
		controller->SetShowMouseCursor(false);
		SetUserFocus(controller);

		RemoveFromParent();
	}
	
	return result;
}
