// Fill out your copyright notice in the Description page of Project Settings.


#include "MoneyItem.h"

AMoneyItem::AMoneyItem()
{
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