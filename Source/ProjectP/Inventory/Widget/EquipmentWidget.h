// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/UIInfo.h"

#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<class UItemSlotWidget> mMainItemSlot = nullptr;
	TObjectPtr<UItemSlotWidget> mSubItemSlot = nullptr;
	TObjectPtr<UItemSlotWidget> mArmorItemSlot = nullptr;
	TObjectPtr<UItemSlotWidget> mPotionItemSlot = nullptr;
	
	virtual void NativeConstruct() override;
	
	void InitSlots() const;

public:
	void SetMainItemSlot(const FItem* item) const;
	void SetPotionItemSlot(const FItem* item, int32 amount) const;
};
