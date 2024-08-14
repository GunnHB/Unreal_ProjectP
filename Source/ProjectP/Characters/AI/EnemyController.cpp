// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

AEnemyController::AEnemyController()
{
	mPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI_PERCEPTION"));
	mSightSense = CreateDefaultSubobject<UAISense_Sight>(TEXT("SENSE_SIGHT"));
}
