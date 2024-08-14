// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_SetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	bool bIsArrived = false;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool SetMovementSpeed(const APawn* pawn) const;
};
