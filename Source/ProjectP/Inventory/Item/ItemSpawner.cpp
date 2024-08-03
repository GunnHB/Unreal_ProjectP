// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

#include "ItemBase.h"
#include "../../System/Manager/ItemManager.h"
#include "Equipment/Weapon/SwordItem.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(mRoot);

	static ConstructorHelpers::FObjectFinder<UDataTable>
	tableAsset(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Item.DT_Item'"));

	if(tableAsset.Succeeded())
		mItemTableHandler.DataTable = tableAsset.Object;
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnItem();
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnItem()
{
	if (mItemTableHandler.DataTable == nullptr)
		return;

	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FItem* item = CItemManager::GetInstance()->GetData<FItem>(mItemTableHandler.RowName);
	
	if(item == nullptr)
		return;
	
	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotation = GetActorRotation();
	
	mItemActor = GetWorld()->SpawnActor<AItemBase>(item->item_class, spawnLocation, spawnRotation, param);
	
	mItemActor->GetStaticMesh()->SetStaticMesh(item->mesh);
	
	mItemActor->GetCapsule()->SetCapsuleHalfHeight(item->capsule_half_height);
	mItemActor->GetCapsule()->SetCapsuleRadius(item->capsule_radius);
	
	mItemActor->GetCapsule()->SetRelativeTransform(item->capsule_transform);
	mItemActor->GetStaticMesh()->SetRelativeRotation(item->mesh_transform.Rotator());
}