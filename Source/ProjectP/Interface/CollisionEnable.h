// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "CollisionEnable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCollisionEnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTP_API ICollisionEnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UStaticMeshComponent* GetMesh() = 0;
	virtual FQuat GetQuat() = 0;
	virtual void TrailBegin() = 0;
	virtual void TrailEnd() = 0;
};
