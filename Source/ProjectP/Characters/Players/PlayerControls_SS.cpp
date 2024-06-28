// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControls_SS.h"

#include "PlayerAnimInstance_SS.h"

APlayerControls_SS::APlayerControls_SS()
{
	InitAssets();
	InitComponentValues();
}

#pragma region Base
void APlayerControls_SS::BeginPlay()
{
	Super::BeginPlay();

	mAnimInstance = Cast<UPlayerAnimInstance_SS>(GetMesh()->GetAnimInstance());
}

void APlayerControls_SS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerControls_SS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
#pragma endregion

#pragma region Initialize
void APlayerControls_SS::InitAssets()
{
	// set skeletal
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh>
			asset(TEXT("/Script/Engine.SkeletalMesh'/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));

		if (asset.Succeeded())
			GetMesh()->SetSkeletalMesh(asset.Object);
	}

	// set animinstance
	{
		static ConstructorHelpers::FClassFinder<UAnimInstance>
			asset(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Animations/ABP_PlayerControls_SS.ABP_PlayerControls_SS_C'"));

		if (asset.Succeeded())
			GetMesh()->SetAnimInstanceClass(asset.Class);
	}
}

void APlayerControls_SS::InitComponentValues()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f);
	GetCapsuleComponent()->SetCapsuleRadius(30.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	mSpringArm->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

	mSpringArm->TargetArmLength = 300.f;

	mSpringArm->bInheritYaw = false;
}
#pragma endregion