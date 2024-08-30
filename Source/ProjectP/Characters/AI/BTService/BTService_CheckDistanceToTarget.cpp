// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckDistanceToTarget.h"

void UBTService_CheckDistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	UBlackboardComponent* blackBoardComp = OwnerComp.GetBlackboardComponent();
	
	if(IsValid(pawn) && IsValid(blackBoardComp))
	{
		if(blackBoardComp->GetValueAsBool(GameValue::GetIsAttackingFName()))
			return;
		
		AActor* targetActor = Cast<AActor>(blackBoardComp->GetValueAsObject(GameValue::GetTargetFName()));

		if(!IsValid(targetActor))
			return;
		
		float distance = FVector::Dist(pawn->GetActorLocation(), targetActor->GetActorLocation());

		blackBoardComp->SetValueAsBool(GameValue::GetEnableToCombatFName(), distance < GameValue::GetEnemyCombatPatrolDistance());
	}
}
