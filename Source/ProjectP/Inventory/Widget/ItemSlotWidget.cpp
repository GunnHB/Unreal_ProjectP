// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

void UItemSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mItemImage = Cast<UImage>(GetWidgetFromName(GameValue::GetUIItemImageFName()));
	mItemAmountTextBlock = Cast<UTextBlock>(GetWidgetFromName(GameValue::GetUIItemAmountTextBlockFName()));
}

void UItemSlotWidget::InitSlot(const FItem* itemData)
{
	if(itemData == nullptr)
	{
		ClearSlot();
		return;	
	}
		
	if(IsValid(itemData->item_texture))
		SetItemImage(itemData->item_texture);

	if(itemData->stackable)
		SetItemAmount();
}

void UItemSlotWidget::ClearSlot() const
{
	SetItemImage(nullptr);
	SetItemAmount(-1);
}

void UItemSlotWidget::SetItemImage(UTexture2D* texture) const
{
	if(IsValid(mItemImage))
	{
		if(texture == nullptr)
			mItemImage->SetColorAndOpacity(FLinearColor::Transparent);
		else
		{
			mItemImage->SetColorAndOpacity(FLinearColor::White);	
			mItemImage->SetBrushFromTexture(texture);
		}
	}
}

void UItemSlotWidget::SetItemAmount(const float amount) const
{
	if(IsValid(mItemAmountTextBlock))
	{
		if(amount == -1)
			mItemAmountTextBlock->SetText(FText::FromString(""));
		else
			mItemAmountTextBlock->SetText(FText::FromString(FString::FromInt(amount)));
	}
}
