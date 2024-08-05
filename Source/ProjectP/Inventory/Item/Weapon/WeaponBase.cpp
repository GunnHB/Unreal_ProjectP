// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	
}

void AWeaponBase::OnEquip()
{
	if(mWeaponData == nullptr)
		return;
	
	bIsEquipped = true;
	AttachActor(mWeaponData->hand_socket_name);
}

void AWeaponBase::OnUnequip()
{
	if(mWeaponData == nullptr)
		return;
	
	bIsEquipped = false;
	AttachActor(mWeaponData->sheath_socket_name);
}

void AWeaponBase::SetData(FItem* itemData, bool relocate)
{
	Super::SetData(itemData, relocate);

	if(itemData != nullptr)
		mWeaponData = CItemManager::GetInstance()->mWeaponMap[itemData->ref_id];
}

void AWeaponBase::AttachActor(FName& socketName)
{
	if(mSkeletalMesh == nullptr)
		return;
	
	AttachToComponent(mSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
}
