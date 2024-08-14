// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/AIInfo.h"

#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_MoveToTarget : public UBTTask_MoveTo
{
	GENERATED_BODY()

protected:
	FVector mCurrentTargetLocation = FVector::ZeroVector;

public:
	UBTTask_MoveToTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:
	void SetMovementSpeed(APawn* pawn, float deltaSeconds);
};
