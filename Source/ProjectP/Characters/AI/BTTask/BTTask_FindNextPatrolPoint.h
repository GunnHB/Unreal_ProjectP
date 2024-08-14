// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_FindNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	FVector mTargetLocation = FVector::ZeroVector;
	uint8 mPatrolIndex = 0;
};
