// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPawn.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitAssets();
	InitComponentsValue();
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ��������Ʈ�� ��ϵ� �Լ� ������
	if (mDeathDelegate.IsBound())
		mDeathDelegate.Broadcast();	// ��ϵ� �Լ��� ȣ��
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AAIPawn::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

void AAIPawn::InitAssets()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AAIPawn::InitComponentsValue()
{
	if(mCapsule == nullptr)
		mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));

	if(mSkeletalMesh == nullptr)
		mSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL_MESH"));

	SetRootComponent(mCapsule);
	mSkeletalMesh->SetupAttachment(RootComponent);

	mSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}