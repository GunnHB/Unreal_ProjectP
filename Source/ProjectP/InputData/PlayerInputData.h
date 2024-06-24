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
	UInputMappingContext* mContext;

public:
	UInputAction* mMovementAction;
	UInputAction* mCameraMovementAction;
	UInputAction* mJumpAction;
};
