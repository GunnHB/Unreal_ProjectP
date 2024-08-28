// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mItemImage = Cast<UImage>(GetWidgetFromName(""));
	mItemAmountTextBlock = Cast<UTextBlock>(GetWidgetFromName(""));
}

void UItemSlotWidget::SetItemImage(UTexture2D* texture)
{
	if(IsValid(mItemImage))
		mItemImage->SetBrushFromTexture(texture);
}

void UItemSlotWidget::SetItemAmount(const float amount)
{
	if(IsValid(mItemAmountTextBlock))
		mItemAmountTextBlock->SetText(FText::FromString(FString::FromInt(amount)));
}
