// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"

AWeaponItem::AWeaponItem()
{
	
}

void AWeaponItem::OnEquip()
{
	if(mWeaponData == nullptr)
		return;
	
	AttachActor(mWeaponData->hand_socket_name);
	isEquipped = true;
}

void AWeaponItem::OnUnequip()
{
	if(mWeaponData == nullptr)
		return;
	
	AttachActor(mWeaponData->sheath_socket_name);
	isEquipped = false;
}

void AWeaponItem::AttachActor(FName& socketName)
{
	AttachToComponent(mSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
}
