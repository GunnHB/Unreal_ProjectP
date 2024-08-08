// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "ProjectP/Interface/Combatable.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATIC_MESH"));

	SetRootComponent(mCapsule);
	mStaticMesh->SetupAttachment(mCapsule);

	mStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::SetData(FItem* itemData, bool relocate)
{
	if(itemData != nullptr)
		mItemData = itemData;
	
	SetItem(relocate);
}

void AItemBase::Interact(AActor* targetActor)
{
	ICombatable* combatable = Cast<ICombatable>(targetActor);

	if(combatable != nullptr)
		combatable->PickUpItem(this);
}

void AItemBase::SetItem(const bool relocate) const
{
	mCapsule->SetCapsuleHalfHeight(mItemData->capsule_half_height);
	mCapsule->SetCapsuleRadius(mItemData->capsule_radius);

	mStaticMesh->SetStaticMesh(mItemData->mesh);
	
	if(relocate)
	{
		mStaticMesh->SetRelativeLocation(mItemData->mesh_transform.GetLocation());
		mStaticMesh->SetRelativeRotation(mItemData->mesh_transform.GetRotation());

		mCapsule->SetCollisionProfileName(TEXT("Item"));
	}
	else
		mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

