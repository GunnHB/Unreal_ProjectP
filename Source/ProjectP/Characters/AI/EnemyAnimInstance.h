// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AnimInstanceBase.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UEnemyAnimInstance : public UAnimInstanceBase
{
	GENERATED_BODY()

protected:
	TObjectPtr<class AAIPawn> mAIPawn = nullptr;
	TObjectPtr<class UEnemyMovementComponent> mAIMovement = nullptr;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
