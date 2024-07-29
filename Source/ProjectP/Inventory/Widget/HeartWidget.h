// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/UIInfo.h"
#include "Blueprint/UserWidget.h"
#include "HeartWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UHeartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<UImage> mHeartImage = nullptr;

protected:
	virtual void NativeConstruct() override;
};
