// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DrawSheath.h"

EBTNodeResult::Type UBTTask_DrawSheath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();

	if(!IsValid(blackboardComp))
		return EBTNodeResult::Aborted;


	return result;
}
