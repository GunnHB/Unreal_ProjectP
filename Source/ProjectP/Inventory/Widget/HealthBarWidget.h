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
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<class UHeartWidget> mHeartWidgetClass = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UWrapBox> mHealthBarWrapBox = nullptr;
	
	TArray<UHeartWidget*> mHeartArray;
	int8 mLastIndex = 0;

	virtual void NativeConstruct() override;

public:
	void InitHealthBar(const float maxHP, const float currHP);
	void SetCurrHealthBar(const float value);
};
