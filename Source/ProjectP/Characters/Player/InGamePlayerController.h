// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"

#include "GameFramework/PlayerController.h"
#include "ProjectP/Data/InventoryData.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	TObjectPtr<class UInventoryDataAsset> mDataAsset = nullptr;
	FItem* mMainItem = nullptr;

	FTimerHandle mHPTimer;

	uint8 mLoopCount = 0;

public:
	AInGamePlayerController();

	void InitPlayerHealthBar(const float maxValue, const float currValue) const;
	void SetPlayerStamina(const float value, const bool isExhausted = false) const;
	void SetInventoryData(class UInventoryData* data) const;
	
	void StartHPTimer(const uint8 value);

	UInventoryDataAsset* GetDataAsset() const {return mDataAsset;}
	
protected:
	virtual void BeginPlay() override;

	void EndHPTimer();
};
