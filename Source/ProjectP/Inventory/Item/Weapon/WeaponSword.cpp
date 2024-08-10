// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSword.h"

#include "../../../Component/CollisionComponent.h"

AWeaponSword::AWeaponSword()
{
	mCapsule->SetRelativeRotation(FRotator(0.f,-90.f, 90.f));

	mCollision = CreateDefaultSubobject<UCollisionComponent>(TEXT("COLLISION"));
}

void AWeaponSword::SetData(FItem* itemData, bool relocate)
{
	Super::SetData(itemData, relocate);
	
	if(mWeaponData != nullptr)
		mSwordData = CItemManager::GetInstance()->mSwordTable->FindRow<FSword>(mWeaponData->ref_row_name, "");
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

void AWeaponSword::ResetTransform()
{
	mStaticMesh->SetRelativeLocation(FVector::ZeroVector);
	mStaticMesh->SetRelativeRotation(FRotator::ZeroRotator);

	mCapsule->SetRelativeLocation(FVector::ZeroVector);
	mCapsule->SetRelativeRotation(FRotator::ZeroRotator);
}
