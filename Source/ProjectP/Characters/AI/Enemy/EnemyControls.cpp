// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyControls.h"

AEnemyControls::AEnemyControls()
{
	SetPerception();
}

void AEnemyControls::BeginPlay()
{
	Super::BeginPlay();

	mAIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyControls::OnTargetDetect);		// �� �߰�
	mAIPerception->OnTargetPerceptionForgotten.AddDynamic(this, &AEnemyControls::OnTargetForget);	// �� ��ħ
}

void AEnemyControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyControls::SetPerception()
{
	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION"));

	// ��Ʈ�ѷ��� ���� ����� ����
	// ���ڰ� ���۷����̱� ������ ��ü�� �Ѱ���� ��
	// �������� �Ѱ��ֱ�
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

		mSightConfig->SightRadius = 2000.f;								// �þ� �Ÿ�
		mSightConfig->LoseSightRadius = 2500.f;							// ��ġ�� �Ÿ�
		mSightConfig->PeripheralVisionAngleDegrees = 45.f;				// �ݰ�
	
		mSightConfig->DetectionByAffiliation.bDetectEnemies = true;		// ����
		mSightConfig->DetectionByAffiliation.bDetectFriendlies = true;	// �Ʊ�
		mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;	// �߸�

		// �þ� ������ ��� (�迭�� ���)
		// ���ο����� �ݺ����� ������ ���ο� �������� Ȯ��
		// ���� �ߺ��Ǵ� ������ ����ϰ� �Ǹ� �ű� �������� �����Ѵ�.
		mAIPerception->ConfigureSense(*mSightConfig);
	}

	// ��ǥ ���� ��� ����
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
	// �����ϴ� target�� ���Ͱ� �ƴ� ��Ʈ�ѷ�
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
