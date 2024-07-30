// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyItem.h"

#include "../../../Characters/Player/PlayerControls.h"

AMoneyItem::AMoneyItem()
{
	mCapsule->SetCapsuleHalfHeight(30.f);
	mCapsule->SetCollisionProfileName(TEXT("Money"));

	mCapsule->SetRelativeLocation(FVector(0.f, 0.f, 30.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		moneyAsset(TEXT("/Script/Engine.StaticMesh'/Game/04_Inventory/Model/02_Money/Green/3DModel/SM_RupeeGreen.SM_RupeeGreen'"));
	
	if(moneyAsset.Succeeded())
		mStaticMesh->SetStaticMesh(moneyAsset.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable>
		tableAsset(TEXT("/Script/Engine.DataTable'/Game/04_Inventory/DataTable/DT_Money.DT_Money'"));

	if(tableAsset.Succeeded())
		mMoney.DataTable = tableAsset.Object;
}

void AMoneyItem::BeginPlay()
{
	Super::BeginPlay();
}

void AMoneyItem::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::CollisionBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	APlayerControls* pControl = Cast<APlayerControls>(OtherActor);
	
	if(!IsValid(pControl) || mMoneyData == nullptr)
		return;
	
	if(pControl->AddMoney(mMoneyData))
		Destroy();
}
