// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SetMovementSpeed.h"

EBTNodeResult::Type UBTTask_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ownerPawn = Cast<APawn>(OwnerComp.GetOwner());

	if(IsValid(ownerPawn))
		SetMovementSpeed(ownerPawn);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UBTTask_SetMovementSpeed::SetMovementSpeed(const APawn* owner) const
{
	UFloatingPawnMovement* movement = owner->FindComponentByClass<UFloatingPawnMovement>();

	if(IsValid(movement))
		movement->MaxSpeed = GameValue::GetMaxWalkSpeed();
}