// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mDegreee = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mAcceleration = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mIsInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mPlayJumpAnim = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector mAimVector;

	// variables
	bool mAttackState = false;
	bool mAttackCombo = false;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();

public:
	void PlayJumpAnim();

	// getter
	bool GetIsInAir() const { return mIsInAir; }

private:
	void SetAimOffset(class APlayerControls* pControl);
};
