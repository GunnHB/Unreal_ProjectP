// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FocusToTarget.h"

#include "../EnemyPawn.h"

void UBTService_FocusToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* blackBoardComp = OwnerComp.GetBlackboardComponent();
	AEnemyPawn* pawn = OwnerComp.GetAIOwner()->GetPawn<AEnemyPawn>();
	
	if(!IsValid(blackBoardComp) || !IsValid(pawn))
		return;

	if(blackBoardComp->GetValueAsObject(GameValue::GetTargetFName()) != nullptr)
	{
		FVector targetLocation = Cast<AActor>(blackBoardComp->GetValueAsObject(GameValue::GetTargetFName()))->GetActorLocation();

		FVector targetVector = pawn->GetActorLocation() - targetLocation;

		if(targetVector.Normalize())
		{
			float dotProduct = FVector::DotProduct(pawn->GetActorForwardVector(), targetVector);
			float angle = FMath::RadiansToDegrees(FMath::Acos(dotProduct));

			angle *= FVector::CrossProduct(pawn->GetActorForwardVector(), targetVector).Z > 0 ? 1 : -1;
			
			pawn->SetAimOffsetDegree(angle);

			UE_LOG(ProjectP, Warning, TEXT("%f"), angle);
		}
	}
}
