// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnActor.h"

#include "AIPawn.h"

// Sets default values
AAISpawnActor::AAISpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(mRoot);

	// �����Ϳ����� ����� �������� ó��
#if WITH_EDITORONLY_DATA
	mArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));

	mArrow->SetupAttachment(mRoot);

	mRoot->bVisualizeComponent = true;
#endif
}

// Called when the game starts or when spawned
void AAISpawnActor::BeginPlay()
{
	Super::BeginPlay();

	Spawn();
}

// Called every frame
void AAISpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ������ ���� ������ ���ŵǾ� nullptr
	if (!mSpawnActor)
	{
		mCalculateSpawnTime += DeltaTime;

		if (mSpawnTime <= mCalculateSpawnTime)
		{
			mCalculateSpawnTime = 0.f;
			Spawn();
		}
	}
}

void AAISpawnActor::Spawn()
{
	// ��ȿ�� �˻�� ������ ���� ������ �׳� ����
	if (!IsValid(mSpawnClass))
		return;

	// ����
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	// �׻� ������

	// ���� �� spawnactor�� ��ġ�� �������� �������� ������
	// ���� �� �Ʒ��� ���� �� �ִ�. �׷��� ��ġ �����ؾߵ�
	// �����Ǵ� ��ġ ��������
	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotator = GetActorRotation();

	// uclass�� class default object�� ������ �ִ�.
	AAIPawn* defaultPawn = mSpawnClass->GetDefaultObject<AAIPawn>();

	if (IsValid(defaultPawn))
	{
		// ���� ������ Ʈ�������� �������� Z ���� �����ϰ� �Ǹ�
		// ĸ���� ���� ���̵� ���� �����ž� ��
		// ��Ȯ�� ���� ���̸� ��� ���� GetScaledCapsuleHalfHeight�� ���

		// ���� ��ġ �ø���
		spawnLocation.Z += defaultPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	}

	// ���� (����)
	mSpawnActor = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass, spawnLocation, spawnRotator);

	// ������ ���� ��������Ʈ�� �Լ� ���
	if (mSpawnActor != nullptr)
		// ThisClass -> ���� Ŭ����
		// ���� ���ŵ� �� �ش� �Լ��� ȣ���
		mSpawnActor->AddDeathDelegate<ThisClass>(this, &AAISpawnActor::AIDeathDelegate);
}

void AAISpawnActor::AIDeathDelegate()
{
}