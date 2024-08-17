// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"
#include "../../../System/AIInfo.h"

#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_WaitToKeepEnemyInCheck.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_WaitToKeepEnemyInCheck : public UBTTask_Wait
{
	GENERATED_BODY()

public:
	UBTTask_WaitToKeepEnemyInCheck();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
};
