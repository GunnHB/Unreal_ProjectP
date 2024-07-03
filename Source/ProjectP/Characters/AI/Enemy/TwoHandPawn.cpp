// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoHandPawn.h"

ATwoHandPawn::ATwoHandPawn()
{
	InitAssets();
	InitComponentsValue();
}

void ATwoHandPawn::InitAssets()
{
	Super::InitAssets();

	// mesh
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh>
			asset(TEXT("/Script/Engine.SkeletalMesh'/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Manny_Weapon.SKM_Manny_Weapon'"));

		if (asset.Succeeded())
			mSkeletalMesh->SetSkeletalMesh(asset.Object);
	}
}

void ATwoHandPawn::InitComponentsValue()
{
	Super::InitComponentsValue();

	mCapsule->SetCapsuleHalfHeight(90.f);
	mCapsule->SetCapsuleRadius(30.f);

	mSkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	mSkeletalMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}
