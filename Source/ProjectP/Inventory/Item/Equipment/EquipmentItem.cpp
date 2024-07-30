// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem.h"

AEquipmentItem::AEquipmentItem()
{
	mStaticMesh->SetRelativeRotation(FRotator::ZeroRotator);
}

void AEquipmentItem::OnEquipped()
{
	bIsEquipped = true;

	AttachActor(mAttachSocketName);
}

void AEquipmentItem::UnEquipped()
{
	bIsEquipped = false;
}

void AEquipmentItem::AttachActor(const FName& socketName)
{
	AttachToComponent(mSkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
}
