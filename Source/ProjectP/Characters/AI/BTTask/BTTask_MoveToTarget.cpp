// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"

#include "../AIPawn.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = GameValue::GetBTTaskMoveToTargetFName();
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	bNotifyTick = true;
	mCurrentTargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GameValue::GetTargetLocationFName());

	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();

	if (IsValid(pawn))
	{
		mActorLocationForDistance = pawn->GetActorLocation();
		mCurrentYaw = pawn->GetActorRotation().Yaw;
	}
	
	return result;
}

void UBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ownerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if(!IsValid(ownerPawn))
		return;
		
	UFloatingPawnMovement* movement = ownerPawn->FindComponentByClass<UFloatingPawnMovement>();

	if(IsValid(movement))
	{
		SetCurrentActorLocation(ownerPawn);
		SetCurrentActorRotation(ownerPawn, DeltaSeconds);
		SetMovementSpeed(movement, DeltaSeconds);
	}
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

void UBTTask_MoveToTarget::SetCurrentActorLocation(APawn* pawn)
{
	if (!IsValid(pawn))
		return;

	AAIPawn* aiPawn = Cast<AAIPawn>(pawn);

	if(IsValid(aiPawn))
	{
		mActorLocationForDistance = pawn->GetActorLocation();
		mActorLocationForDistance.Z -= aiPawn->GetCapsuleComp()->GetScaledCapsuleHalfHeight();

		// 공중에 뜨는 현상 방지인데 맘에 안듦
		aiPawn->SetActorLocation(FVector(aiPawn->GetActorLocation().X, aiPawn->GetActorLocation().Y,aiPawn->GetCapsuleComp()->GetScaledCapsuleHalfHeight()));
	}
}

void UBTTask_MoveToTarget::SetMovementSpeed(UFloatingPawnMovement* movement, float deltaSeconds) const
{
	if(!IsValid(movement))
		return;
	
	float distance = FVector::Dist(mActorLocationForDistance, mCurrentTargetLocation);
	float targetSpeed = distance > GameValue::GetMoveToTargetLimitAmount() ? GameValue::GetWalkSpeed() : 0.f;

	// 약간 하드코딩인디...
	if(IsValid(movement))
		movement->MaxSpeed = FMath::FInterpTo(movement->MaxSpeed, targetSpeed, deltaSeconds, 5.f);
}

void UBTTask_MoveToTarget::SetCurrentActorRotation(APawn* pawn, float deltaSeconds)
{
	if(!IsValid(pawn))
		return;
	
	FVector direction = mCurrentTargetLocation - mActorLocationForDistance;

	if(direction.Normalize())
	{
		float targetYaw = FMath::Atan2(direction.Y, direction.X) * FMathf::RadToDeg;

		if (targetYaw < -180.f)
			targetYaw = 360 + targetYaw;
		else if (targetYaw > 180.f)
			targetYaw = targetYaw - 360.f;
		
		mCurrentYaw = FMath::FInterpTo(mCurrentYaw, targetYaw, deltaSeconds, 5.f);

		pawn->SetActorRotation(FRotator(0.f, mCurrentYaw, 0.f));
	}
}
