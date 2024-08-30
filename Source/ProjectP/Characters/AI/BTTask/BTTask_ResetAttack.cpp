// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ResetAttack.h"

EBTNodeResult::Type UBTTask_ResetAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GameValue::GetAttackableFName(), true);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GameValue::GetTargetLocationFName(), FVector::ZeroVector);

	return result;
}
