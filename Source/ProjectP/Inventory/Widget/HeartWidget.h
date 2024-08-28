// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/UIInfo.h"

#include "Blueprint/UserWidget.h"
#include "HeartWidget.generated.h"

namespace EHeartType
{
	enum Type : uint8
	{
		Empty = 0,
		OneQuarter,
		Half,
		ThreeQuarter,
		Full,
	};
}

UCLASS()
class PROJECTP_API UHeartWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<UImage> mHeartImage = nullptr;
	EHeartType::Type mHeartType = EHeartType::Empty;
	
	virtual void NativeConstruct() override;

public:
	void SetHeart(EHeartType::Type type);
	EHeartType::Type GetHeartType() const {return mHeartType;}
	
	bool IsEmpty() const {return mHeartType == EHeartType::Empty;}
};