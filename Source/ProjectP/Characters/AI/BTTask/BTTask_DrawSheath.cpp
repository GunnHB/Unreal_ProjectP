// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DrawSheath.h"

#include "../EnemyPawn.h"
#include "../../../Component/CombatComponent.h"
#include "ProjectP/Inventory/Item/Weapon/WeaponBase.h"

EBTNodeResult::Type UBTTask_DrawSheath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();

	if(!IsValid(blackboardComp))
		return EBTNodeResult::Aborted;
	
	bool drawSheathFlag = blackboardComp->GetValueAsBool(GameValue::GetWasDrawFName());
	AEnemyPawn* enemyPawn = OwnerComp.GetAIOwner()->GetPawn<AEnemyPawn>();

	// 지금은 사용하지 않아서 우선 주석 처리
	// if(IsValid(enemyPawn))
	// 	enemyPawn->TryDrawSheath(drawSheathFlag);

	blackboardComp->SetValueAsBool(GameValue::GetWasDrawFName(), !drawSheathFlag);

	return result;
}
