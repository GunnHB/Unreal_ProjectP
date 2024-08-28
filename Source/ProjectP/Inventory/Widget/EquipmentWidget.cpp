// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"

#include "ItemSlotWidget.h"
#include "../../System/Manager/ItemManager.h"

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mMainItemSlot = Cast<UItemSlotWidget>(GetWidgetFromName(GameValue::GetUIMainItemSlotFName()));
	mSubItemSlot = Cast<UItemSlotWidget>(GetWidgetFromName(GameValue::GetUISubItemSlotFName()));
	mArmorItemSlot = Cast<UItemSlotWidget>(GetWidgetFromName(GameValue::GetUIArmorItemSlotFName()));
	mPotionItemSlot = Cast<UItemSlotWidget>(GetWidgetFromName(GameValue::GetUIPotionItemSlotFName()));

	InitSlots();
}

void UEquipmentWidget::InitSlots() const
{
	if(IsValid(mMainItemSlot))
		mMainItemSlot->ClearSlot();

	if(IsValid(mSubItemSlot))
		mSubItemSlot->ClearSlot();

	if(IsValid(mArmorItemSlot))
		mArmorItemSlot->ClearSlot();

	if(IsValid(mPotionItemSlot))
		mPotionItemSlot->ClearSlot();
}

void UEquipmentWidget::InitMainItem(const FName& rowName) const
{
	FItem* item = CItemManager::GetInstance()->mItemTable->FindRow<FItem>(rowName, "");

	if(item != nullptr)
		mMainItemSlot->InitSlot(item);
}
