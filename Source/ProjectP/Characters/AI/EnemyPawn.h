// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AI/AIPawn.h"
#include "EnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AEnemyPawn : public AAIPawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UEnemyMovementComponent> mMovement = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UCombatComponent> mCombat = nullptr;

	FEnemy mEnemyData;

public:
	AEnemyPawn();
};
