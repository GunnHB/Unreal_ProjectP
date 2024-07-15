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
	// montages
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> mAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> mAttackSectionArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 mCurrentAttackSection = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mDegreee = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mAcceleration = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mIsInAir = false;

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
	// montage
	void PlayAttackMontage();
	UFUNCTION()
	void MontageEnded(UAnimMontage* montage, bool bInterrupted);

	void DoJump();

private:
	UFUNCTION()
	void AnimNotify_Combo();
	UFUNCTION()
	void AnimNotify_ResetCombo();
};
