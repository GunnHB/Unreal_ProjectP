// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/UIInfo.h"

#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TArray<class UHeartWidget*> mHeartArray;

public:
	void SetHealthBar(const float value) const;
};
