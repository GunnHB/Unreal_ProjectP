// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordItem.h"

ASwordItem::ASwordItem()
{
}

void ASwordItem::BeginPlay()
{
	Super::BeginPlay();
}

void ASwordItem::SetData(FSword* data)
{
	if(data == nullptr)
		return;

	mSwordData = data;

	SetWeaponData(CItemManager::GetInstance()->GetWeaponDataByRefId(data->id));
}
