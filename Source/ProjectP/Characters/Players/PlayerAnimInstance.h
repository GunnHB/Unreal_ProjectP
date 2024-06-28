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
	// Montages
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackRecoveryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> mAttackSectionArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 mCurrentAttackSection = 0;

protected:
	// vairables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mVelocity = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float mMoveDir = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mAcceleration = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool mIsInAir = false;

	bool mAttackCombo = false;
	bool mAttackState = false;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();

public:
	void PlayAttackMontage();

public:
	UFUNCTION()
	void AnimNotify_AttackCombo();
	UFUNCTION()
	void AnimNotify_AttackComboEnd();
	UFUNCTION()
	void AnimNotify_AttackEnable();
	UFUNCTION()
	void AnimNotify_AttackDisable();

private:
	UFUNCTION()
	void MontageEnd(UAnimMontage* montage, bool bInterrupted);

public:
	// getter
	bool GetAttackState() { return mAttackState; }
	bool GetAttackCombo() { return mAttackCombo; }

	// setter
	void SetAttackState(const bool& value) { mAttackState = value; }
	void SetAttackCombo(const bool& value) { mAttackCombo = value; }

public:
	void ResetDatas()
	{
		mAttackState = false;
		mAttackCombo = false;

		mCurrentAttackSection = 0;
	}
};
