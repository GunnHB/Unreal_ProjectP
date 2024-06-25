// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControls_Crunch.h"

APlayerControls_Crunch::APlayerControls_Crunch()
{
	InitAssets();
	InitCompoValues();
}

void APlayerControls_Crunch::BeginPlay()
{
}

void APlayerControls_Crunch::Tick(float DeltaTime)
{
}

void APlayerControls_Crunch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void APlayerControls_Crunch::InitAssets()
{
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

void APlayerControls_Crunch::InitCompoValues()
{
}