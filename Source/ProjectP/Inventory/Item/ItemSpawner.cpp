// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

#include "ItemBase.h"
#include "../../System/Manager/ItemManager.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(mRoot);
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	if(mItemTableHandler.DataTable == nullptr)
		return;

	FItem* item = CItemManager::GetInstance()->GetData<FItem>(mItemTableHandler.RowName);

	if(item == nullptr)
		return;
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

