// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SetMovementSpeed.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ownerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if(!IsValid(ownerPawn))
		return EBTNodeResult::Failed;

	return SetMovementSpeed(ownerPawn) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}

bool UBTTask_SetMovementSpeed::SetMovementSpeed(const APawn* pawn) const
{
	UFloatingPawnMovement* movement = pawn->FindComponentByClass<UFloatingPawnMovement>();

	if(!IsValid(movement))
		return false;
	
	movement->MaxSpeed = GameValue::GetWalkSpeed();

	return true;
}