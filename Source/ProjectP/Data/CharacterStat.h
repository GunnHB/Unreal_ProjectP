// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "CharacterStat.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UCharacterStat : public UObject
{
	GENERATED_BODY()
	
protected:
	float mCurrCharacterHP;
	float mCurrCharacterStamina;
	
	float mMaxCharacterHP;
	float mMaxCharacterStamina;

public:
	virtual void InitStat(const APawn* owner);
	
	// getteer
	float GetCurrCharacterHP() const {return mCurrCharacterHP;}
	float GetCurrCharacterStamina() const {return mCurrCharacterStamina;}
	float GetMaxCharacterHP() const {return mMaxCharacterHP;}
	float GetMaxCharacterStamina() const {return mMaxCharacterStamina;}
	
	// setter
	void SetCurrCharacterHP(const float value) {mCurrCharacterHP = value;}
	void SetCurrCharacterStamina(const float value) {mCurrCharacterStamina = value;}
	void SetMaxCharacterHP(const float value) {mMaxCharacterHP = value;}
	void SetMaxCharacterStamina(const float value) {mMaxCharacterStamina = value;}
	
	bool IsCharacterDead() const {return mCurrCharacterHP <= 0;}
};
