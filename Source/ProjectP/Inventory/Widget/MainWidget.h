// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/UIInfo.h"

#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<class UHealthBarWidget> mHealthBarWidget = nullptr;
	TObjectPtr<class UStaminaWidget> mStaminaWidget = nullptr;

	virtual void NativeConstruct() override;

public:
	void SetPlayerHP(const float value) const;
	void SetPlayerStamina(const float value, const bool isExhausted = false) const;
};
