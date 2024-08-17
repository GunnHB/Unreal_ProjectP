// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"

#include "Perception/AISenseConfig_Sight.h"

AEnemyController::AEnemyController()
{
	mPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION"));
	mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SENSE_SIGHT"));

	SetPerceptionComponent(*mPerceptionComp);
	SetSightValue();

	mPerceptionComp->ConfigureSense(*mSightConfig);
	mPerceptionComp->SetDominantSense(mSightConfig->GetSenseImplementation());

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
	bbAsset(TEXT("/Script/AIModule.BlackboardData'/Game/07_AI/BB_Enemy.BB_Enemy'"));

	if(bbAsset.Succeeded())
		mBlackboard = bbAsset.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		btAsset(TEXT("/Script/AIModule.BehaviorTree'/Game/07_AI/BT_Enemy.BT_Enemy'"));

	if(btAsset.Succeeded())
		mBehaviorTree = btAsset.Object;
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	mPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnTargetDetect);
	mPerceptionComp->OnTargetPerceptionForgotten.AddDynamic(this, &AEnemyController::OnTargetForget);
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

void AEnemyController::OnTargetDetect(AActor* target, FAIStimulus stimulus)
{
	if(stimulus.WasSuccessfullySensed())
	{
		UE_LOG(ProjectP, Warning, TEXT("Sense Success"));
		
		AController* controller = Cast<AController>(target);

		if(IsValid(controller))
			target = controller->GetPawn<AActor>();

		if(target != Blackboard->GetValueAsObject(GameValue::GetTargetFName()))
			Blackboard->SetValueAsObject(GameValue::GetTargetFName(), target);
	}
	else
	{
		UE_LOG(ProjectP, Warning, TEXT("Sense Fail"));
		
		Blackboard->SetValueAsObject(GameValue::GetTargetFName(), nullptr);
		Blackboard->SetValueAsBool(GameValue::GetKeepEnemyInCheckFName(), true);
	}
}

void AEnemyController::OnTargetForget(AActor* target)
{
	UE_LOG(ProjectP, Warning, TEXT("%s misssssssss!"), *target->GetName());
	
	GetBlackboardComponent()->SetValueAsObject(GameValue::GetTargetFName(), nullptr);
}

void AEnemyController::SetSightValue() const
{
	mSightConfig->SightRadius = GameValue::GetEnemySightRadius();
	mSightConfig->LoseSightRadius = GameValue::GetEnemyLoseSightRadius();
	mSightConfig->PeripheralVisionAngleDegrees = GameValue::GetEnemyVisionAngleDegree();

	mSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	mSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
}
