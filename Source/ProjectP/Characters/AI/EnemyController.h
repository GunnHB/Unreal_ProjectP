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
	TObjectPtr<UAISenseConfig_Damage> mDamageConfig = nullptr;
	
	TObjectPtr<UBlackboardData> mBlackboard = nullptr;
	TObjectPtr<UBehaviorTree> mBehaviorTree = nullptr;

	TObjectPtr<class UMainWidget> mMainWidget = nullptr;
	TObjectPtr<class UEnemyHealthBarWidget> mEnemyHPWidget = nullptr;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void Tick(float DeltaSeconds) override;

	// ufunction
	UFUNCTION() void OnTargetDetect(AActor* target, FAIStimulus stimulus);
	UFUNCTION() void OnTargetForget(AActor* target);

public:
	void SetEnemyHP(const float value);

private:
	void SetSightValue() const;
};
