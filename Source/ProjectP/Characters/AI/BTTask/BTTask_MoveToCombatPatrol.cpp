// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToCombatPatrol.h"

#include "AIController.h"
#include "../../../Characters/AI/EnemyPawn.h"

UBTTask_MoveToCombatPatrol::UBTTask_MoveToCombatPatrol()
{
	NodeName = "MoveToCombatPatrol";
}

EBTNodeResult::Type UBTTask_MoveToCombatPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	bool bDoPatrol = FMath::RandRange(0, 100) % 2 == 0;

	if(!bDoPatrol)
		return EBTNodeResult::Failed;

	mEnemyPawn = OwnerComp.GetAIOwner()->GetPawn<AEnemyPawn>();
	mBlackboardComp = OwnerComp.GetBlackboardComponent();

	if(!IsValid(mEnemyPawn) || !IsValid(mBlackboardComp))
		return EBTNodeResult::Aborted;

	SetCombatPatrolLocation(FMath::RandRange(0, 100) % 2 == 0);
	
	return result;
}

void UBTTask_MoveToCombatPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_MoveToCombatPatrol::SetCombatPatrolLocation(const bool value) const
{
	FVector combatPatrolLocation = mEnemyPawn->GetActorLocation() + FVector(0.f, 100.f * (value ? -1.f : 1.f), 0.f);
	
	mBlackboardComp->SetValueAsVector(GameValue::GetCombatPatrolLocationFName(), combatPatrolLocation);
}
