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
		URotateComponent* rotateComp = pawn->FindComponentByClass<URotateComponent>();
		AActor* targetActor = Cast<AActor>(blackBoardComp->GetValueAsObject(GameValue::GetTargetFName()));

		if(IsValid(rotateComp) && IsValid(targetActor))
		{
			float angle = rotateComp->GetAngle(targetActor);
			
			pawn->SetAimOffsetDegree(angle);
			pawn->SetMovementDegree(angle);
		}
	}

#if ENABLE_DRAW_DEBUG
	if(!pawn->IsDead())
		TryDrawDebugLine(blackBoardComp, pawn);
#endif
}


#if ENABLE_DRAW_DEBUG
void UBTService_FocusToTarget::TryDrawDebugLine(UBlackboardComponent* blackBoardComp, AActor* owner)
{
	if(!IsValid(blackBoardComp))
		return;

	AActor* targetActor = Cast<AActor>(blackBoardComp->GetValueAsObject(GameValue::GetTargetFName()));

	if(IsValid(targetActor))
		DrawDebugLine(GetWorld(), owner->GetActorLocation(), targetActor->GetActorLocation(), FColor::Cyan, false, .05f, 0, 1.f);
}
#endif
