// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitToKeepEnemyInCheck.h"

#include "../../../Characters/AI/EnemyPawn.h"

UBTTask_WaitToKeepEnemyInCheck::UBTTask_WaitToKeepEnemyInCheck()
{
	NodeName = GameValue::GetBTTaskWaitToKeepEnemyInCheckFString();
}

EBTNodeResult::Type UBTTask_WaitToKeepEnemyInCheck::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	WaitTime = GameValue::GetKeepEnemyInCheckTime();

	UBlackboardComponent* blackBoardComp = OwnerComp.GetBlackboardComponent();

	if(IsValid(blackBoardComp))
		blackBoardComp->SetValueAsBool(GameValue::GetKeepEnemyInCheckFName(), false);

	AEnemyPawn* enemyPawn = OwnerComp.GetAIOwner()->GetPawn<AEnemyPawn>();

	if(IsValid(enemyPawn))
		enemyPawn->ReleaseGuard();

	return result;
}