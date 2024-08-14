// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/AIInfo.h"

#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController();

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UAIPerceptionComponent> mPerceptionComp = nullptr;
	TObjectPtr<UAISense_Sight> mSightSense = nullptr;
};
