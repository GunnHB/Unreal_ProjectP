// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "../../Component/EnemyMovementComponent.h"
#include "../../Component/CombatComponent.h"

AEnemyPawn::AEnemyPawn()
{
	mMovement = CreateDefaultSubobject<UEnemyMovementComponent>(TEXT("MOVEMENT"));
	mCombat = CreateDefaultSubobject<UCombatComponent>(TEXT("COMBAT"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		meshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/EssentialAnimation/SwordShield/Demo/Mannequin/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));

	if(meshAsset.Succeeded())
		mMesh->SetSkeletalMesh(meshAsset.Object);

	mCapsule->SetCapsuleHalfHeight(89.f);
	mCapsule->SetCapsuleRadius(22.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -89.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}