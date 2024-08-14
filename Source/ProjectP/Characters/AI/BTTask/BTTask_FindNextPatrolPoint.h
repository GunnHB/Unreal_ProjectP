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
	uint8 mPatrolIndex = 0;

	TObjectPtr<class AEnemyPawn> mOwnerEnemy;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool SetPathLocation(UBlackboardComponent* blackboard);
	void IncreasePathIndex(UBlackboardComponent* blackboard);
};
