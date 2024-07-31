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

	// anim flag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation Flag") bool mPlayJumpAnim = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation Flag") bool mPlayDrawWeaponAnim = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation Flag") bool mPlaySheathWeaponAnim = false;

	// montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Montage") TObjectPtr<UAnimMontage> mDrawWeaponMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Montage") TObjectPtr<UAnimMontage> mSheathWeaponMontage = nullptr;

	// variables
	bool mAttackState = false;
	bool mAttackCombo = false;

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

	// setter
	void SetPlayJumpAnim(const bool value) {mPlayJumpAnim = value;}
	// void SetPlayDrawWeaponAnim(const bool value) {mPlayDrawWeaponAnim = value;}
	// void SetPlaySheathWeaponAnim(const bool value) {mPlaySheathWeaponAnim = value;}
	
	void PlayDrawWeaponMontage();
	void PlaySheathWeaponMontage();

private:

	// anim notify
	UFUNCTION() void AnimNotify_DrawWeapon();
	UFUNCTION() void AnimNotify_SheathWeapon();
};
