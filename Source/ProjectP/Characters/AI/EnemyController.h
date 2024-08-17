// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
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
	TObjectPtr<UAISenseConfig_Sight> mSightConfig = nullptr;
	
	TObjectPtr<UBlackboardData> mBlackboard = nullptr;
	TObjectPtr<UBehaviorTree> mBehaviorTree = nullptr;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	// ufunction
	UFUNCTION() void OnTargetDetect(AActor* target, FAIStimulus stimulus);
	UFUNCTION() void OnTargetForget(AActor* target);

private:
	void SetSightValue() const;
};
