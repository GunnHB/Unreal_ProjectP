// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"

#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// TObjectPtr<class UMainWidget> mMainWidget = nullptr;
	// TSubclassOf<UMainWidget> mMainWidgetClass = nullptr;

	TObjectPtr<class UInventoryDataAsset> mDataAsset = nullptr;

	FTimerHandle mHPTimer;

	uint8 mLoopCount = 0;

public:
	AInGamePlayerController();

	void InitPlayerHealthBar(const float maxValue, const float currValue) const;
	void SetPlayerStamina(const float value, const bool isExhausted = false) const;
	void SetInventoryData() const;
	
	void StartHPTimer(const uint8 value);
	
protected:
	virtual void BeginPlay() override;

	void EndHPTimer();
};
