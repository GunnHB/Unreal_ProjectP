// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../System/GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mVelocity = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveDir = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mAcceleration = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mIsInAir = false;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();
};
