// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	UPROPERTY(EditAnywhere) FName mAttachSocketName;
	
	TObjectPtr<USkeletalMeshComponent> mSkeletalMesh = nullptr;
	
private:
	bool bIsEquipped = false;

public:
	AEquipmentItem();
	
	// getter
	bool GetIsEquipped() const {return bIsEquipped;}

	// setter
	void SetIsEquipped(const bool value) {bIsEquipped = value;}
	void SetSkeletalMesh(USkeletalMeshComponent* value) {mSkeletalMesh = value;}
	void SetNoCollision() const {mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);}

	void OnEquipped(const FName& socketName);
	void OnUnequipped(const FName& socketName);

protected:
	void AttachActor();
};
