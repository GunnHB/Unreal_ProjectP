// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputMappingContext.h"
#include "InputAction.h"

#include "../System/GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "PlayerInputData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerInputData : public UObject
{
	GENERATED_BODY()

public:
	UPlayerInputData();

public:
	TObjectPtr<UInputMappingContext> mContext = nullptr;

public:
	TObjectPtr<UInputAction> mInputToMovement = nullptr;
	TObjectPtr<UInputAction> mInputToCameraMovement = nullptr;
	TObjectPtr<UInputAction> mInputToLightAttack = nullptr;
	TObjectPtr<UInputAction> mInputToHeavyAttack = nullptr;
	TObjectPtr<UInputAction> mInputToJump = nullptr;
	TObjectPtr<UInputAction> mInputToFocus = nullptr;
	TObjectPtr<UInputAction> mInputToDrawSheath = nullptr;
	TObjectPtr<UInputAction> mInputToInteract = nullptr;
	TObjectPtr<UInputAction> mInputToDodge = nullptr;
	TObjectPtr<UInputAction> mInputToSprint = nullptr;

	TObjectPtr<UInputAction> mInputToInventory = nullptr;
	TObjectPtr<UInputAction> mInputToEquipment = nullptr;
};
