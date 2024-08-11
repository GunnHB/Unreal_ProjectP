// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Equippable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEquippable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTP_API IEquippable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetOwner(AActor* actor) = 0;
	virtual void OnEquip() = 0;
	virtual void OnUnequip() = 0;

protected:
	virtual void AttachActor(FName& socketName) = 0;
};
