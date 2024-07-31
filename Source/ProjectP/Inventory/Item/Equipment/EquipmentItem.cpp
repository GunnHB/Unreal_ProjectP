// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem.h"

#include "../../../Characters/Player/PlayerControls.h"

AEquipmentItem::AEquipmentItem()
{
	mStaticMesh->SetRelativeRotation(FRotator::ZeroRotator);
}

void AEquipmentItem::OnEquipped(const FName& socketName)
{
	bIsEquipped = true;
	mAttachSocketName = socketName;

	AttachActor();
}

void AEquipmentItem::OnUnequipped(const FName& socketName)
{
	bIsEquipped = false;
	mAttachSocketName = socketName;

	AttachActor();
}

void AEquipmentItem::AttachActor()
{
	AttachToComponent(mSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, mAttachSocketName);
}
