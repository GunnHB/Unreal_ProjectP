// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ResetValue.h"

#include "../EnemyPawn.h"

EBTNodeResult::Type UBTTask_ResetValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* blackboardComponent = OwnerComp.GetBlackboardComponent();

	if(!IsValid(blackboardComponent))
		return EBTNodeResult::Failed;

	blackboardComponent->SetValueAsBool(GameValue::GetEnableToCombatFName(), false);
	blackboardComponent->SetValueAsBool(GameValue::GetAttackableFName(), false);
	blackboardComponent->SetValueAsObject(GameValue::GetTargetFName(), nullptr);

	AEnemyPawn* enemyPawn = OwnerComp.GetAIOwner()->GetPawn<AEnemyPawn>();

	if(!IsValid(enemyPawn))
		return EBTNodeResult::Failed;

	enemyPawn->SetAimOffsetDegree(0.f);
	enemyPawn->SetMovementDegree(0.f);

	return EBTNodeResult::Succeeded;
}
