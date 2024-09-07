// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "UObject/Interface.h"
#include "Recoverable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URecoverable : public UInterface
{
	GENERATED_BODY()
};

class PROJECTP_API IRecoverable
{
	GENERATED_BODY()
	
public:
	virtual void Recovery() = 0;
};
