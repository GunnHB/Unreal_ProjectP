// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"
#include "../../../System/AIInfo.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ResetValue.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_ResetValue : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
