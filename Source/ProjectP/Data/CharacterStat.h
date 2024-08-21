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

private:
	float mCharacterHealth = 88.f;
	float mCharacterStamina = 100.f;

public:
	// getteer
	float GetCharacterHealth() const {return mCharacterHealth;}
	float GetCharacterStamina() const {return mCharacterStamina;}
	
	// setter
	void SetCharacterHealth(float value) {mCharacterHealth = value;}
	void SetCharacterStamina(float value) {mCharacterStamina = value;}
	
	bool IsCharacterDead() const {return mCharacterHealth <= 0;}
};
