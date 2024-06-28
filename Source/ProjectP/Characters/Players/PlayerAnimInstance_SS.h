// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "../../System/GameInfo.h"
#include "Animation/AnimInstance.h"
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

	// variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mVelocity = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mAcceleration = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool mIsInAir = false;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	virtual void NativeUninitializeAnimation() override;

	virtual void NativeBeginPlay() override;

protected:
	UFUNCTION()
	void AnimNotify_Combo();
	UFUNCTION()
	void AnimNotify_ResetCombo();
};
