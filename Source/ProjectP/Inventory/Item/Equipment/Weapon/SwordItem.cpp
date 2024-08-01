// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordItem.h"

ASwordItem::ASwordItem()
{
}

ASwordItem::ASwordItem(FSword* sword)
{
	if(sword == nullptr)
		return;

	mSwordData = sword;
}

void ASwordItem::BeginPlay()
{
	Super::BeginPlay();

	if(mSwordData == nullptr)
		return;
}
