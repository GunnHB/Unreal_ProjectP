// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "../../Component/EnemyMovementComponent.h"
#include "../../Component/CombatComponent.h"
#include "EnemyAnimInstance.h"

AEnemyPawn::AEnemyPawn()
{
	mMovement = CreateDefaultSubobject<UEnemyMovementComponent>(TEXT("MOVEMENT"));
	mCombat = CreateDefaultSubobject<UCombatComponent>(TEXT("COMBAT"));

	mCapsule->SetCapsuleHalfHeight(89.f);
	mCapsule->SetCapsuleRadius(22.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -89.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mCapsule->SetCollisionProfileName(GameValue::GetEnemyFName());
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		meshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/EssentialAnimation/SwordShield/Demo/Mannequin/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));

	if(meshAsset.Succeeded())
		mMesh->SetSkeletalMesh(meshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		animAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Animations/AI/ABP_EnemyControls.ABP_EnemyControls_C'"));

	if(animAsset.Succeeded())
		mMesh->SetAnimInstanceClass(animAsset.Class);
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(mMesh->GetAnimInstance()))
		mAnimInstance = Cast<UEnemyAnimInstance>(mMesh->GetAnimInstance());
}

float AEnemyPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return damage;
}

void AEnemyPawn::ContinueAttack()
{
}

void AEnemyPawn::DrawSheath()
{
}

void AEnemyPawn::EnableCombat()
{
}

void AEnemyPawn::ResetAttack()
{
}

void AEnemyPawn::ResetCombat()
{
}

void AEnemyPawn::ResetDodge()
{
}

void AEnemyPawn::ResetTakeDamage()
{
}

void AEnemyPawn::TakeDamage(APawn* hitterPawn)
{
}

void AEnemyPawn::StartHitStop(const float time)
{
}

void AEnemyPawn::EndHitStop()
{
}
