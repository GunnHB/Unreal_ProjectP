// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitToCombatPatrol.h"

UBTTask_WaitToCombatPatrol::UBTTask_WaitToCombatPatrol()
{
	NodeName = "WaitToCombatPatrol";
}

EBTNodeResult::Type UBTTask_WaitToCombatPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	WaitTime = FMath::RandRange(3.f, 7.f);

	return result;
}