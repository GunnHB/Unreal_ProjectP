// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Combatable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTP_API ICombatable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ContinueAttack() = 0;
	virtual void EnableCombat() = 0;
	virtual void DrawSheath() = 0;
	virtual void ResetAttack() = 0;
	virtual void ResetDodge() = 0;
	virtual void ResetCombat() = 0;
	virtual void ResetTakeDamage() = 0;
	virtual void ResetMontage() = 0;
};
