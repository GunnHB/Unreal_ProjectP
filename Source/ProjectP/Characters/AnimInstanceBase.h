// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

private:
	TObjectPtr<APawn> mPawn = nullptr;
	TObjectPtr<UPawnMovementComponent> mPawnMovement = nullptr;

protected:
	// getter
	APawn* GetThisPawn() const {return mPawn;}
	UPawnMovementComponent* GetThisPawnMovement() const {return mPawnMovement;}

	// base variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float mSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float mDegree = 0.f;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
