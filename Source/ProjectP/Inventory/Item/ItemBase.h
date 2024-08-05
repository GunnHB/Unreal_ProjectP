// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/Manager/ItemManager.h"

#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class PROJECTP_API AItemBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UCapsuleComponent> mCapsule = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> mStaticMesh = nullptr;

	FItem* mItemData = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	// getter
	UCapsuleComponent* GetCapsule() const {return mCapsule;}
	UStaticMeshComponent* GetStaticMesh() const {return mStaticMesh;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// getter
	FItem* GetThisItemData() const {return mItemData;}

	// setter
	virtual void SetData(FItem* itemData, bool relocate);

private:
	void SetItem(const bool relocate) const;
};
