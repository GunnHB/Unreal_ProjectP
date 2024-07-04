// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyControls.h"

AEnemyControls::AEnemyControls()
{
	SetPerception();
}

void AEnemyControls::BeginPlay()
{
	Super::BeginPlay();

	mAIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyControls::OnTargetDetect);		// 적 발견
	mAIPerception->OnTargetPerceptionForgotten.AddDynamic(this, &AEnemyControls::OnTargetForget);	// 적 놓침
}

void AEnemyControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyControls::SetPerception()
{
	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION"));

	// 컨트롤러의 감각 기관을 세팅
	// 인자가 레퍼런스이기 때문에 객체를 넘겨줘야 함
	// 역참조로 넘겨주기
	SetPerceptionComponent(*mAIPerception);

	SetPerceptionSense();
}

void AEnemyControls::SetPerceptionSense()
{
	mHearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("SENSE_HEARING"));
	mDamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("SENSE_DAMAGE"));

	// sight
	{
		mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SENSE_SIGHT"));

		mSightConfig->SightRadius = 2000.f;								// 시야 거리
		mSightConfig->LoseSightRadius = 2500.f;							// 놓치는 거리
		mSightConfig->PeripheralVisionAngleDegrees = 45.f;				// 반각
	
		mSightConfig->DetectionByAffiliation.bDetectEnemies = true;		// 적군
		mSightConfig->DetectionByAffiliation.bDetectFriendlies = true;	// 아군
		mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;	// 중립

		// 시야 감각을 등록 (배열에 등록)
		// 내부에서는 반복문을 돌리며 새로운 감각인지 확인
		// 만약 중복되는 감각을 등록하게 되면 신규 감각으로 재등록한다.
		mAIPerception->ConfigureSense(*mSightConfig);
	}

	// 대표 감각 기관 설정
	mAIPerception->SetDominantSense(mSightConfig->GetSenseImplementation());
}

void AEnemyControls::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyControls::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyControls::OnTargetDetect(AActor* target, FAIStimulus stimulus)
{
	// 감지하는 target은 액터가 아닌 컨트롤러
	if (stimulus.WasSuccessfullySensed())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("enemy!!!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("detect failed"));
	}
}

void AEnemyControls::OnTargetForget(AActor* target)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("no enemy..."));
}
