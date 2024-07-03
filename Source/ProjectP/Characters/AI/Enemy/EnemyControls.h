// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../../System/GameInfo.h"
#include "AIController.h"
#include "EnemyControls.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AEnemyControls : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyControls();

protected:
	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* mAIPerception = nullptr;

	UAISenseConfig_Sight* mSightConfig = nullptr;
	UAISenseConfig_Hearing* mHearingConfig = nullptr;
	UAISenseConfig_Damage* mDamageConfig = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void SetPerception();
	void SetPerceptionSense();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UFUNCTION()
	void OnTargetDetect(AActor* target, FAIStimulus stimulus);
	UFUNCTION()
	void OnTargetForget(AActor* target);
};
