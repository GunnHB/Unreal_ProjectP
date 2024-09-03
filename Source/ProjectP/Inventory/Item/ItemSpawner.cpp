// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"

#include "ItemBase.h"
#include "Weapon/WeaponSword.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	mArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));

	SetRootComponent(mRoot);
	mArrow->SetupAttachment(mRoot);

	mArrow->ArrowColor = FColor(150, 200, 255);
	mArrow->bTreatAsASprite = true;
	mArrow->SetupAttachment(mRoot);
	mArrow->bIsScreenSizeScaled = true;
	mArrow->SetSimulatePhysics(false);

	static ConstructorHelpers::FObjectFinder<UDataTable>
		tableAsset(TEXT("/Script/Engine.DataTable'/Game/06_DataTable/Item/DT_Item.DT_Item'"));
	
	if(tableAsset.Succeeded())
		mTableHandle.DataTable = tableAsset.Object;
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	if(mTableHandle.DataTable == nullptr)
		return;

	SpawnItem();
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemSpawner::SpawnItem() const
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	
	FItem* itemData = CItemManager::GetInstance()->GetItemTable()->FindRow<FItem>(mTableHandle.RowName, "");

	if(itemData == nullptr)
		return;

	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotation = GetActorRotation();

	AItemBase* spawnItem = GetWorld()->SpawnActor<AItemBase>(itemData->item_class, spawnLocation, spawnRotation, param);

	if(IsValid(spawnItem))
		spawnItem->SetData(itemData, true);
}

