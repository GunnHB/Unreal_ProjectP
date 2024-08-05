// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATIC_MESH"));
	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));

	SetRootComponent(mStaticMesh);
	mCapsule->SetupAttachment(mStaticMesh);
	
	mStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mCapsule->SetCollisionProfileName(TEXT("Item"));
	mCapsule->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::Initialize(FItem* item)
{
	if(item == nullptr)
		return;

	mItem = item;
}