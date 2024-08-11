// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/Manager/ItemManager.h"
#include "../..//Interface/Interactable.h"

#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FAddIgnoreActorDelegate)

UCLASS()
class PROJECTP_API AItemBase : public AActor, public IInteractable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UCapsuleComponent> mCapsule = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> mStaticMesh = nullptr;

	FItem* mItemData = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FAddIgnoreActorDelegate mAddActorDelegate;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// getter
	FItem* GetThisItemData() const {return mItemData;}

	// setter
	virtual void SetData(FItem* itemData, bool relocate);

	// inteface
	virtual void Interact(AActor* targetActor) override;

private:
	void SetItem(const bool relocate) const;
};
