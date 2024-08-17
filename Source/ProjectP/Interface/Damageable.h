// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DamageEvents.h"

#include "UObject/Interface.h"
#include "Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTP_API IDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void TakeDamage(APawn* hitterPawn) = 0;
	virtual void StartHitStop(const float time) = 0;
	virtual void EndHitStop() = 0;
};
