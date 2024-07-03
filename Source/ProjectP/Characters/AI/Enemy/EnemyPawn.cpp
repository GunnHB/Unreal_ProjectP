// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "EnemyMovement.h"
#include "EnemyControls.h"

AEnemyPawn::AEnemyPawn()
{
	mMovement = CreateDefaultSubobject<UEnemyMovement>(TEXT("MOVEMENT"));

	InitComponentsValue();
}

void AEnemyPawn::InitComponentsValue()
{
	Super::InitComponentsValue();

	mMovement->SetUpdatedComponent(RootComponent);
	AIControllerClass = AEnemyControls::StaticClass();  // enemy 종류들은 EnemyControls를 생성

	mCapsule->SetCollisionProfileName(TEXT("Enemy"));	// 충돌 세팅
}
