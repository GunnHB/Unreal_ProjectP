// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "PlayerAnimInstance_SS.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerAnimInstance_SS : public UAnimInstance
{
	GENERATED_BODY()

protected:
	// Montages
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> mAttackSectionArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 mCurrentAttckSection;

protected:
	// variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mVelocity = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mAcceleration = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mIsInAir = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mJump = false;

	// for attack
	bool mAttackCombo = false;
	bool mAttackState = false;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	virtual void NativeUninitializeAnimation() override;

	virtual void NativeBeginPlay() override;

public:
	// Montages
	void PlayAttackMontage();

	UFUNCTION()
	void AnimNotify_Combo();
	UFUNCTION()
	void AnimNotify_ResetCombo();

	// Jumps
	void OnJump()
	{
		mJump = true;
	}

private:
	void MontageEnd(UAnimMontage* montage, bool bInterrupted);
};
