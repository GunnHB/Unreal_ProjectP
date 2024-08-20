// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectP/System/GameInfo.h"
#include "../../../System/AIInfo.h"

#include "BehaviorTree/BTService.h"
#include "BTService_CheckDistanceToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTService_CheckDistanceToTarget : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
