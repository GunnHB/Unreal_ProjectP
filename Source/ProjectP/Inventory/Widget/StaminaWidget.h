// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/UIInfo.h"

#include "Blueprint/UserWidget.h"
#include "StaminaWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<UImage> mStaminaImage = nullptr;

	virtual void NativeConstruct() override;

public:
	void SetStamina(const float value) const;
};
