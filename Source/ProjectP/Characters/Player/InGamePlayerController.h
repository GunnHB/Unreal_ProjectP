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

public:
	AInGamePlayerController();
	
	void SetPlayerHP(const float value) const;
	void SetPlayerStamina(const float value, const bool isExhausted = false) const;

protected:
	virtual void BeginPlay() override;
};
