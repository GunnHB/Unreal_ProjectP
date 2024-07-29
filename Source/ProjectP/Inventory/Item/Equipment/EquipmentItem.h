// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"
#include "../ItemBase.h"
#include "EquipmentItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AEquipmentItem : public AItemBase
{
	GENERATED_BODY()

protected:
	FName mAttachSocketName;
	bool bIsEquipped = false;

public:
	AEquipmentItem();

protected:
	void OnEquipped();
	void UnEquipped();
	void AttachActor(const FName& socketName);
};
