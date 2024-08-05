// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSword.h"

AWeaponSword::AWeaponSword()
{
	mCapsule->SetRelativeRotation(FRotator(0.f,-90.f, 90.f));
}

void AWeaponSword::SetData(FItem* itemData, bool relocate)
{
	Super::SetData(itemData, relocate);
	
	if(mWeaponData != nullptr)
		mSwordData = CItemManager::GetInstance()->mSwordMap[mWeaponData->ref_id];
}

void AWeaponSword::ResetTransform()
{
	mStaticMesh->SetRelativeLocation(FVector::ZeroVector);
	mStaticMesh->SetRelativeRotation(FRotator::ZeroRotator);

	mCapsule->SetRelativeLocation(FVector::ZeroVector);
	mCapsule->SetRelativeRotation(FRotator::ZeroRotator);
}
