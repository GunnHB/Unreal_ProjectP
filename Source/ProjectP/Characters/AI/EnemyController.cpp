// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

AEnemyController::AEnemyController()
{
	mPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION"));
	mSightSense = CreateDefaultSubobject<UAISense_Sight>(TEXT("SENSE_SIGHT"));

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
	bbAsset(TEXT("/Script/AIModule.BlackboardData'/Game/07_AI/BB_Enemy.BB_Enemy'"));

	if(bbAsset.Succeeded())
		mBlackboard = bbAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		btAsset(TEXT("/Script/AIModule.BehaviorTree'/Game/07_AI/BT_Enemy.BT_Enemy'"));

	if(btAsset.Succeeded())
		mBehaviorTree = btAsset.Object;
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	if (IsValid(mBlackboard) && IsValid(mBehaviorTree))
	{
		UBlackboardComponent* BlackboardRef = nullptr;
		
		if (UseBlackboard(mBlackboard, BlackboardRef))
			RunBehaviorTree(mBehaviorTree);
	}

	Super::OnPossess(InPawn);
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
}
