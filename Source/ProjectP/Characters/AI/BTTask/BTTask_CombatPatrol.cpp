// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CombatPatrol.h"

EBTNodeResult::Type UBTTask_CombatPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UBTTask_CombatPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
