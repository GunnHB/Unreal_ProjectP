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

	// 에디터에서만 기즈모가 나오도록 처리
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

	// 스폰한 폰이 죽으면 제거되어 nullptr
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
	// 유효성 검사로 스폰할 폰이 없으면 그냥 리턴
	if (!IsValid(mSpawnClass))
		return;

	// 스폰
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	// 항상 스폰됨

	// 스폰 시 spawnactor의 위치를 기준으로 가져오기 때문에
	// 폰이 땅 아래로 빠질 수 있다. 그래서 위치 조정해야됨
	// 스폰되는 위치 가져오기
	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotator = GetActorRotation();

	// uclass는 class default object를 가지고 있다.
	AAIPawn* defaultPawn = mSpawnClass->GetDefaultObject<AAIPawn>();

	if (IsValid(defaultPawn))
	{
		// 만약 액터의 트랜스폼의 스케일의 Z 값을 수정하게 되면
		// 캡슐의 절반 길이도 따라 수정돼야 함
		// 정확한 절반 길이를 얻기 위해 GetScaledCapsuleHalfHeight를 사용

		// 액터 위치 올리기
		spawnLocation.Z += defaultPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	}

	// 스폰 (생성)
	mSpawnActor = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass, spawnLocation, spawnRotator);

	// 생성된 폰의 델리게이트에 함수 등록
	if (mSpawnActor != nullptr)
		// ThisClass -> 현재 클래스
		// 폰이 제거될 때 해당 함수가 호출됨
		mSpawnActor->AddDeathDelegate<ThisClass>(this, &AAISpawnActor::AIDeathDelegate);
}

void AAISpawnActor::AIDeathDelegate()
{
}