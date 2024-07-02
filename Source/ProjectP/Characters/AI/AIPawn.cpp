// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPawn.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	mSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL_MESH"));

	SetRootComponent(mCapsule);
	mSkeletalMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAIPawn::InitAssets()
{
	// mesh
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh>
			asset(TEXT(""));

		if (asset.Succeeded())
			mSkeletalMesh->SetSkeletalMesh(asset.Object);
	}
}

void AAIPawn::InitComponentsValue()
{
	mCapsule->SetCapsuleHalfHeight(90.f);
	mCapsule->SetCapsuleRadius(30.f);

	mSkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	mSkeletalMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}