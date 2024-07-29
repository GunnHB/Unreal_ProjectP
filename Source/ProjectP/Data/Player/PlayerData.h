// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerData : public UObject
{
	GENERATED_BODY()

private:
	int32 mPlayerHealth = 100;
	int32 mPlayerStamina = 100;
	int32 mPlayerMoney = 0;

public:
	// getter
	int32 GetPlayerMoney() const {return mPlayerMoney;};

	// setter
	void SetPlayerMoney(const int32 value) {mPlayerMoney = value;}
};
