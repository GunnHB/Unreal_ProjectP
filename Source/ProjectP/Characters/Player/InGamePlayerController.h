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
	TObjectPtr<class UMainWidget> mMainWidget;
	TSubclassOf<UMainWidget> mMainWidgetClass;

	FTimerHandle mHPTimer;

	uint8 mLoopCount = 0;

public:
	AInGamePlayerController();
	
	void SetPlayerMaxHP(const float value) const;
	void SetPlayerStamina(const float value, const bool isExhausted = false) const;

	void SetPlayerCurrHP(const float value);

protected:
	virtual void BeginPlay() override;
	void StartHPTimer(const float damage);
	void EndHPTimer();
};
