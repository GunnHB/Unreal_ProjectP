// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"

#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToCombatPatrol.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_MoveToCombatPatrol : public UBTTask_MoveTo
{
	GENERATED_BODY()

protected:
	TObjectPtr<class AEnemyPawn> mEnemyPawn = nullptr;
	TObjectPtr<UBlackboardComponent> mBlackboardComp = nullptr;

public:
	UBTTask_MoveToCombatPatrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	void SetCombatPatrolLocation(const bool value) const;
};
