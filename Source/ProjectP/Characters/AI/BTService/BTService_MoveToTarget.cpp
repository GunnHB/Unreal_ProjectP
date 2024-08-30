// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_MoveToTarget.h"

void UBTService_MoveToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* blackBoardComp = OwnerComp.GetBlackboardComponent();
	APawn* ownerPawn = OwnerComp.GetAIOwner()->GetPawn();

	if(IsValid(blackBoardComp))
	{
		if(!blackBoardComp->GetValueAsBool(GameValue::GetIsAttackingFName()))
			return;

		APawn* targetPawn = Cast<APawn>(blackBoardComp->GetValueAsObject(GameValue::GetTargetFName()));

		if(IsValid(targetPawn) && IsValid(ownerPawn))
		{
			FVector lastTargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GameValue::GetTargetLocationFName());
			FVector newLocation = FMath::VInterpTo(ownerPawn->GetActorLocation(), lastTargetLocation, GetWorld()->GetDeltaSeconds(), 10.f);

			

			if(FVector::Dist(ownerPawn->GetActorLocation(), lastTargetLocation) > 100.f)
				ownerPawn->SetActorLocation(newLocation);
		}
	}
}
