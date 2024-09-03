// Fill out your copyright notice in the Description page of Project Settings.

#include "PotionBase.h"

APotionBase::APotionBase()
{
}

void APotionBase::SetData(FItem* itemData, bool relocate)
{
	Super::SetData(itemData, relocate);

	if(itemData != nullptr)
		mPotionData = CItemManager::GetInstance()->GetPotionTable()->FindRow<FPotion>(itemData->ref_row_name, "");
}
