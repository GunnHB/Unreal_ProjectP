// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSword.h"

#include "../../../Component/CollisionComponent.h"

AWeaponSword::AWeaponSword()
{
	mCapsule->SetRelativeRotation(FRotator(0.f,-90.f, 90.f));

	mCollision = CreateDefaultSubobject<UCollisionComponent>(TEXT("COLLISION"));
	mTrailParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE_SYSTEM"));

	if(IsValid(mTrailParticleSystemComp))
	{
		mTrailParticleSystemComp->SetupAttachment(mStaticMesh);

		static ConstructorHelpers::FObjectFinder<UParticleSystem>
			particleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_Ausar/P_AU_Sword_Proj_Trail_01.P_AU_Sword_Proj_Trail_01'"));

		if(particleAsset.Succeeded())
			mTrailParticleSystemComp->SetTemplate(particleAsset.Object);
	}
}

void AWeaponSword::BeginPlay()
{
	Super::BeginPlay();

	mAddActorDelegate.AddUObject(this, &AWeaponSword::AddIgnoreActor);

	TrailEnd();
}

void AWeaponSword::SetData(FItem* itemData, bool relocate)
{
	Super::SetData(itemData, relocate);
	
	if(mWeaponData != nullptr)
		mSwordData = CItemManager::GetInstance()->GetSwordTable()->FindRow<FSword>(mWeaponData->ref_row_name, "");
}

UStaticMeshComponent* AWeaponSword::GetMesh()
{
	return mStaticMesh;
}

FQuat AWeaponSword::GetQuat()
{
	FQuat result;
	
	if(mItemData->mesh_transform.GetRotation() == FQuat::Identity)
		result = FRotationMatrix::MakeFromZ(GetMesh()->GetUpVector()).ToQuat();
	else
		result = FRotationMatrix::MakeFromZ(GetMesh()->GetRightVector()).ToQuat();
	
	return result;
}

void AWeaponSword::TrailBegin()
{
	if(IsValid(mTrailParticleSystemComp))
		mTrailParticleSystemComp->BeginTrails(GameValue::GetCollisionStartSocketName(), GameValue::GetCollisionEndSocketName(), ETrailWidthMode_FromCentre, 1);
}

void AWeaponSword::TrailEnd()
{
	if(IsValid(mTrailParticleSystemComp))
		mTrailParticleSystemComp->EndTrails();
}

void AWeaponSword::ResetTransform()
{
	mStaticMesh->SetRelativeLocation(FVector::ZeroVector);
	mStaticMesh->SetRelativeRotation(FRotator::ZeroRotator);

	mCapsule->SetRelativeLocation(FVector::ZeroVector);
	mCapsule->SetRelativeRotation(FRotator::ZeroRotator);
}

void AWeaponSword::AddIgnoreActor()
{
	mCollision->AddIgnoreActor(mOwner);
}
