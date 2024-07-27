// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
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

	friend class APlayerControls;
	friend class UInventoryWidget;

private:
	int32 mPlayerMoney = 0;
};
