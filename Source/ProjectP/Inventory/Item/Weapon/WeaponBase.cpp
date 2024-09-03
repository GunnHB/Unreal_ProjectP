// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	
}

void AWeaponBase::SetData(FItem* itemData, bool relocate)
{
	Super::SetData(itemData, relocate);

	if(itemData != nullptr)
		mWeaponData = CItemManager::GetInstance()->GetWeaponTable()->FindRow<FWeapon>(itemData->ref_row_name, "");
}

void AWeaponBase::SetOwner(AActor* actor)
{
	if(!IsValid(actor))
		return;

	mOwner = actor;

	if(mAddActorDelegate.IsBound())
		mAddActorDelegate.Broadcast();
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

void AWeaponBase::AttachActor(FName& socketName)
{
	if(mSkeletalMesh == nullptr)
		return;
	
	AttachToComponent(mSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
}
