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
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float mDegreee = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float mSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool mAcceleration = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool mIsInAir = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bInputForMovement = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bIsOneHandWeapon = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bIsEquipped = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bIsDodge = false;

	// anim flag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation Flag") bool bIsLandingAnimEnd = true;

	// anim montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Montages") TObjectPtr<UAnimMontage> mBaseDodgeMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Montages") TObjectPtr<UAnimMontage> mBaseRollMontage;
	
	TObjectPtr<UAnimMontage> mDrawWeaponMontage = nullptr;
	TObjectPtr<UAnimMontage> mSheathWeaponMontage = nullptr;
	TObjectPtr<UAnimMontage> mAttackMontage = nullptr;
	TObjectPtr<UAnimMontage> mDodgeMontage = nullptr;
	TObjectPtr<UAnimMontage> mRollMontage = nullptr;

	// cache
	TObjectPtr<class APlayerControls> mPlayer = nullptr;
	TObjectPtr<UCharacterMovementComponent> mPlayerMovement = nullptr;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	virtual void NativeUninitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	// getter
	bool GetIsInAir() const { return mIsInAir; }
	bool GetIsLandingAnimEnd() const {return bIsLandingAnimEnd;}

	// play montage
	void PlayDrawWeaponMontage();
	void PlaySheathWeaponMontage();

	void PlayAttackMontage(int32 attackIndex, bool randomIndex);
	void TryPlayDodgeMontage(bool isRoll);

private:
	void PerformPlayMontage(UAnimMontage* montage);
	
	// anim notify
	UFUNCTION() void AnimNotify_LandEnd();
};
