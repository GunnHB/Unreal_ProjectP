// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitToKeepEnemyInCheck.h"

UBTTask_WaitToKeepEnemyInCheck::UBTTask_WaitToKeepEnemyInCheck()
{
	NodeName = GameValue::GetBTTaskWaitToKeepEnemyInCheckFString();
}

EBTNodeResult::Type UBTTask_WaitToKeepEnemyInCheck::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	WaitTime = GameValue::GetKeepEnemyInCheckTime();

	return result;
}

void UBTTask_WaitToKeepEnemyInCheck::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	UBlackboardComponent* blackBoardComp = OwnerComp.GetBlackboardComponent();

	if(IsValid(blackBoardComp))
		blackBoardComp->SetValueAsBool(GameValue::GetKeepEnemyInCheckFName(), false);
}