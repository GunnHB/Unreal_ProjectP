// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyActor.h"

#include "../../Characters/Player/PlayerControls.h"

// Sets default values
AMoneyActor::AMoneyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	
	SetRootComponent(mCapsule);
	mMesh->SetupAttachment(mCapsule);

	static ConstructorHelpers::FObjectFinder<UDataTable>
	tableAsset(TEXT("/Script/Engine.DataTable'/Game/04_Inventory/DataTable/DT_Money.DT_Money'"));

	if(tableAsset.Succeeded())
		mMoney.DataTable = tableAsset.Object;

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mCapsule->SetCollisionProfileName(TEXT("Money"));

	mCapsule->SetCapsuleHalfHeight(30.f);
}

// Called when the game starts or when spawned
void AMoneyActor::BeginPlay()
{
	Super::BeginPlay();

	mCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMoneyActor::CollisionBeginOverlap);
}

// Called every frame
void AMoneyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoneyActor::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerControls* pControl = Cast<APlayerControls>(OtherActor);

	FMoney* data = mMoney.GetRow<FMoney>("");

	if(data == nullptr || !IsValid(pControl))
		return;

	if(pControl->AddMoney(data))
		Destroy();
}