// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem.h"

AEquipmentItem::AEquipmentItem()
{
	
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
	UMeshComponent* parent = Cast<ACharacter>(GetOwner())->GetMesh();
	
	AttachToComponent(parent, FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
}
