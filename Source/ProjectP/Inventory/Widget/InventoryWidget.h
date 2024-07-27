// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "../../System/GameInfo.h"
#include "../../System/UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// variable
	TObjectPtr<UTextBlock> mMoneyText = nullptr;

	// override
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	void InitWidget();
	void InitAssets();

	void SetMoneyText();
	
	void SetMode(const FInputModeDataBase& mode, bool showCursor);
	
	APawn* GetOwnerPlayerPawn() const { return GetOwningPlayer() != nullptr ? GetOwningPlayer()->GetPawn() : nullptr; }
};