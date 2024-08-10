// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../Interface/CollisionEnable.h"

#include "WeaponBase.h"
#include "WeaponSword.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AWeaponSword : public AWeaponBase, public ICollisionEnable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UCollisionComponent> mCollision = nullptr;
	
	FSword* mSwordData = nullptr;

public:
	AWeaponSword();

	FSword* GetSwordData() const {return mSwordData;}
	
	virtual void SetData(FItem* itemData, bool relocate) override;

	// interface
	virtual UStaticMeshComponent* GetMesh() override;
	virtual FQuat GetQuat() override;
	
	void ResetTransform();
};
