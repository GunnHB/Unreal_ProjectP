// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindNextPatrolPoint.h"

#include "../EnemyPawn.h"
#include "../../../Characters/AI/AIPatrolPoint.h"

EBTNodeResult::Type UBTTask_FindNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* bbComp = OwnerComp.GetBlackboardComponent();

	if(IsValid(bbComp))
		mPatrolIndex = bbComp->GetValueAsInt(GameValue::GetPatrolIndexFName());

	mOwnerEnemy = OwnerComp.GetAIOwner()->GetPawn<AEnemyPawn>();

	if(!IsValid(mOwnerEnemy))
		return EBTNodeResult::Failed;

	if(SetPathLocation(bbComp))
	{
		IncreasePathIndex(bbComp);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

bool UBTTask_FindNextPatrolPoint::SetPathLocation(UBlackboardComponent* blackboard)
{
	if(!IsValid(mOwnerEnemy) || !IsValid(blackboard))
		return false;

	if(mOwnerEnemy->GetPatrolPointArray().IsEmpty())
		return false;
	
	if(mOwnerEnemy->GetPatrolPointArray()[mPatrolIndex] != nullptr)
	{
		blackboard->SetValueAsVector(GameValue::GetTargetLocationFName(), mOwnerEnemy->GetPatrolPointArray()[mPatrolIndex]->GetActorLocation());

		return true;
	}

	return false;
}

void UBTTask_FindNextPatrolPoint::IncreasePathIndex(UBlackboardComponent* blackboard)
{
	if(!IsValid(blackboard))
		return;

	++mPatrolIndex;

	if(mPatrolIndex > 2)
		mPatrolIndex = 0;
	
	blackboard->SetValueAsInt(GameValue::GetPatrolIndexFName(), mPatrolIndex);
}
