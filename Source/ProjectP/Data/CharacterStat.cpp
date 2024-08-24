// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStat.h"

void UCharacterStat::InitStat(const APawn* owner)
{
	mCurrCharacterHP = 100.f;
	mCurrCharacterStamina = 100.f;

	mMaxCharacterHP = 100.f;
	mMaxCharacterStamina = 100.f;
}