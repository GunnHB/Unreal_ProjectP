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
	
}

// Called every frame
void AAISpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAISpawnActor::Spawn()
{
	// 유효성 검사로 스폰할 폰이 없으면 그냥 리턴
	if (!IsValid(mSpawnClass))
		return;

	// 스폰
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	// 항상 스폰됨

	// 스폰 시 폰의 위치를 정 가운데로 맞추기 때문에 땅 아래로 빠질 수 있다. 그래서 위치 조정해야됨
	// 스폰될 위치 가져오기
	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotator = GetActorRotation();

	// uclass는 class default object를 가지고 있다.
	AAIPawn* defaultPawn = mSpawnClass->GetDefaultObject<AAIPawn>();

	if (IsValid(defaultPawn))
	{
		//defaultPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
	}
}

