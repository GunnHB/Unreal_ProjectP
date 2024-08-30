// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "../EnemyPawn.h"
#include "../EnemyAnimInstance.h"

#include "../../../Component/CombatComponent.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyPawn* enemyPawn = OwnerComp.GetAIOwner()->GetPawn<AEnemyPawn>();

	if(!IsValid(enemyPawn))
		return EBTNodeResult::Failed;

	UCombatComponent* combat = enemyPawn->GetCombatComp();
	UEnemyAnimInstance* animInstance = enemyPawn->GetAnimInstance();
	
	if(IsValid(combat) && IsValid(animInstance) && !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GameValue::GetIsAttackingFName()))
	{
		combat->SetIsRandomAttack(true);
		combat->PerformAttack(animInstance, mAttackMontage);
		
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GameValue::GetIsAttackingFName(), true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GameValue::GetAttackableFName(), false);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GameValue::GetTargetLocationFName(), Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GameValue::GetTargetFName()))->GetActorLocation());
	}

	return result;
}