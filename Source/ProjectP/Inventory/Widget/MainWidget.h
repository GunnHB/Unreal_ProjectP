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
	TObjectPtr<class UEquipmentWidget> mEquipmentWidget = nullptr;
	TObjectPtr<class UEnemyHealthBarWidget> mEnemyHPWidget = nullptr;

	virtual void NativeConstruct() override;

public:
	void InitPlayerHealthBar(const float maxValue, const float currValue) const;
	void InitEnemyHealthBar(class UEnemyStat* enemyStat) const;
	void SetPlayerStamina(const float value, const bool isExhausted = false) const;
	// void SetEquipmentWidget(const class UInventoryDataAsset* dataAsset) const;
	void SetEquipmentWidget(class UInventoryData* data) const;
	void SetPlayerCurrHealthBar(const float damageValue);

	void ActiveEnemyHP(bool active) const;
};
