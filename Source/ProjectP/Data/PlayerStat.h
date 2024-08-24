// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterStat.h"
#include "PlayerStat.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerStat : public UCharacterStat
{
	GENERATED_BODY()

protected:
	int32 mPlayerMoney = 0;

public:
	virtual void InitStat(const APawn* owner) override;
	
	// getter
	int32 GetPlayerMoney() const {return mPlayerMoney;}

	// setter
	void SetPlayerMoney(int32 value) {mPlayerMoney = value;}
};
