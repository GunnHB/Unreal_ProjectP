// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControls_Crunch.h"

APlayerControls_Crunch::APlayerControls_Crunch()
{
	InitAssets();
	InitComponentValues();
}

void APlayerControls_Crunch::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerControls_Crunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerControls_Crunch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerControls_Crunch::InitAssets()
{
	Super::InitAssets();

	// mesh
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh>
			asset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonCrunch/Characters/Heroes/Crunch/Skins/Tier_3/BlackSite/Meshes/Crunch_Black_Site.Crunch_Black_Site'"));

		if (asset.Succeeded())
			GetMesh()->SetSkeletalMesh(asset.Object);
	}

	// anim instance
	{
		static ConstructorHelpers::FClassFinder<UAnimInstance>
			asset(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Animations/ABP_PlayerControls_Crunch.ABP_PlayerControls_Crunch_C'"));

		if (asset.Succeeded())
			GetMesh()->SetAnimInstanceClass(asset.Class);
	}
}

void APlayerControls_Crunch::InitComponentValues()
{
	Super::InitComponentValues();

	// capsule
	GetCapsuleComponent()->SetCapsuleHalfHeight(130.f);
	GetCapsuleComponent()->SetCapsuleRadius(65.f);

	// mesh
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -130.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, - 90.f, 0.f));

	// spring arm
	mSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	mSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

	mSpringArm->TargetArmLength = 500.f;
}