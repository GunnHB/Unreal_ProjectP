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
	UInputMappingContext* mContext = nullptr;

public:
	UInputAction* mInputToMovement = nullptr;
	UInputAction* mInputToCameraMovement = nullptr;
	UInputAction* mInputToAttack = nullptr;
	UInputAction* mInputToJump = nullptr;
	UInputAction* mInputToSprint = nullptr;
	UInputAction* mInputToFocus = nullptr;

	UInputAction* mInputToInventory = nullptr;
};
