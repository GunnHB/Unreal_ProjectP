// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterControls.h"

// Sets default values
ACharacterControls::ACharacterControls()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	mSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL_MESH"));

	SetRootComponent(mCapsule);
	mSkeletalMesh->SetupAttachment(mCapsule);
}

// Called when the game starts or when spawned
void ACharacterControls::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterControls::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterControls::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterControls::InitAssets()
{
}

void ACharacterControls::InitCompoValues()
{
}

