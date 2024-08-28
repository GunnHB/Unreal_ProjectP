// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"

#include "../AIPawn.h"
#include "../EnemyPawn.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = GameValue::GetBTTaskMoveToTargetFName();
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	bNotifyTick = true;

	UBlackboardComponent* blackBoardComp = OwnerComp.GetBlackboardComponent();

	if(!IsValid(blackBoardComp))
		return EBTNodeResult::Failed;

	if(IsSetTarget(blackBoardComp))
	{
		AActor* targetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GameValue::GetTargetFName()));

		if(IsValid(targetActor))
		{
			mTargetActor = targetActor;
			mCurrentTargetLocation = targetActor->GetActorLocation();
		}
	}
	else
	{
		mTargetActor = nullptr;	
		mCurrentTargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GameValue::GetTargetLocationFName());
	}

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
		SetCurrentActorRotation(ownerPawn);
		SetMovementSpeed(movement, DeltaSeconds);
	}

	UBlackboardComponent* blackBoardComp = OwnerComp.GetBlackboardComponent();
	
	if(IsValid(blackBoardComp) && IsValid(mTargetActor))
		SetGuarding(ownerPawn, blackBoardComp);
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

bool UBTTask_MoveToTarget::IsSetTarget(const UBlackboardComponent* blackBoardComp)
{
	return blackBoardComp->GetValueAsObject(GameValue::GetTargetFName()) != nullptr;
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

		// // 공중에 뜨는 현상 방지인데 맘에 안듦
		// aiPawn->SetActorLocation(FVector(aiPawn->GetActorLocation().X, aiPawn->GetActorLocation().Y,aiPawn->GetCapsuleComp()->GetScaledCapsuleHalfHeight()));
	}
}

void UBTTask_MoveToTarget::SetMovementSpeed(UFloatingPawnMovement* movement, float deltaSeconds) const
{
	if(!IsValid(movement))
		return;

	float speed = GameValue::GetWalkSpeed();

	if(IsValid(mTargetActor))
	{
		float distance = FVector::Dist(movement->GetOwner()->GetActorLocation(), mTargetActor->GetActorLocation());

		if(distance > GameValue::GetEnemyReadyToCombatPatrolDistance())
			speed = GameValue::GetJogSpeed();
	}
	
	float distance = FVector::Dist(mActorLocationForDistance, mCurrentTargetLocation);
	float targetSpeed = distance > GameValue::GetMoveToTargetLimitAmount() ? speed : 0.f;

	if(IsValid(movement))
		movement->MaxSpeed = FMath::FInterpTo(movement->MaxSpeed, targetSpeed, deltaSeconds, 5.f);
}

void UBTTask_MoveToTarget::SetGuarding(APawn* pawn, const UBlackboardComponent* blackBoardComp) const
{
	if(!IsValid(pawn) || !IsValid(blackBoardComp))
		return;

	AEnemyPawn* enemyPawn = Cast<AEnemyPawn>(pawn);

	if(!IsValid(enemyPawn))
		return;

	float distance = FVector::Dist(enemyPawn->GetActorLocation(), mTargetActor->GetActorLocation());

	if(distance < GameValue::GetEnemyReadyToCombatPatrolDistance())
	{
		if(IsValid(enemyPawn))
			enemyPawn->PerformGuard();
	}
	else
	{
		if(IsValid(enemyPawn))
			enemyPawn->ReleaseGuard();
	}
}

void UBTTask_MoveToTarget::SetCurrentActorRotation(APawn* pawn)
{
	if(!IsValid(pawn))
		return;

	if(mTargetActor != nullptr)
		mCurrentTargetLocation = mTargetActor->GetActorLocation();

	URotateComponent* rotate = pawn->FindComponentByClass<URotateComponent>();

	if(IsValid(rotate))
		rotate->SetOwnerRotationByDelta(mCurrentTargetLocation);
}
