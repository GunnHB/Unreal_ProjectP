// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"
#include "EnemyPawn.h"
#include "TwoHandPawn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ATwoHandPawn : public AEnemyPawn
{
	GENERATED_BODY()
	
public:
	ATwoHandPawn();

protected:
	virtual void InitAssets() override;
	virtual void InitComponentsValue() override;
};
