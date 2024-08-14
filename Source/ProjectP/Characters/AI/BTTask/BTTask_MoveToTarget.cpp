// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"

#include "../EnemyPawn.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = GameValue::GetBTTaskMoveToTargetFName();
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	bNotifyTick = true;
	mCurrentTargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GameValue::GetTargetLocationFName());
	
	return result;
}

void UBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ownerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if(IsValid(ownerPawn))
		SetMovementSpeed(ownerPawn, DeltaSeconds);
}

void UBTTask_MoveToTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();

	if(IsValid(pawn))
	{
		UFloatingPawnMovement* movement = Cast<UFloatingPawnMovement>(pawn->GetMovementComponent());

		if(IsValid(movement))
			movement->MaxSpeed = 0.f;
	}
}

void UBTTask_MoveToTarget::SetMovementSpeed(APawn* pawn, float deltaSeconds)
{
	UFloatingPawnMovement* movement = pawn->FindComponentByClass<UFloatingPawnMovement>();
	FVector newLocation = pawn->GetActorLocation();

	AEnemyPawn* enemyPawn = Cast<AEnemyPawn>(pawn);

	if(IsValid(enemyPawn))
		newLocation.Z -= enemyPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	
	float distance = FVector::Dist(newLocation, mCurrentTargetLocation);
	
	float targetSpeed = distance > 50.f ? GameValue::GetMaxWalkSpeed() : 0.f;

	if(IsValid(movement))
		movement->MaxSpeed = FMath::FInterpTo(movement->MaxSpeed, targetSpeed, .2f, 1.f);
}