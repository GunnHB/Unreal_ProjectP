// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"
#include "../../../System/AIInfo.h"

#include "BehaviorTree/BTService.h"
#include "BTService_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTService_MoveToTarget : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
