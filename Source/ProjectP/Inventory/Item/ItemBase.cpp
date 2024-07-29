// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	SetRootComponent(mCapsule);
	mMesh->SetupAttachment(mCapsule);
	
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));		// 정면
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	mCapsule->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::CollisionBeginOverlap);
}

void AItemBase::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

