// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/UIInfo.h"

#include "Blueprint/UserWidget.h"
#include "ItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<UImage> mItemImage = nullptr;
	TObjectPtr<UTextBlock> mItemAmountTextBlock = nullptr;
	
	virtual void NativeConstruct() override;

public:
	void InitSlot(const FItem* itemData, const int32 amount = -1);
	void ClearSlot() const;

private:
	void SetItemImage(UTexture2D* texture) const;
	void SetItemAmount(const float amount) const;
};
