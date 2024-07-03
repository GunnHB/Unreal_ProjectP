// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"
#include "../AIPawn.h"
#include "EnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AEnemyPawn : public AAIPawn
{
	GENERATED_BODY()
	
protected:
	class UEnemyMovement* mMovement = nullptr;

public:
	AEnemyPawn();

protected:
	virtual void InitComponentsValue() override;
};
