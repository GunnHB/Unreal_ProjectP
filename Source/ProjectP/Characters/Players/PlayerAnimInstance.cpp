// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "PlayerControls.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 플레이어 객체 가져오기
	APlayerControls* pControls = Cast<APlayerControls>(TryGetPawnOwner());

	if (!IsValid(pControls))
		return;

	UCharacterMovementComponent* movement = pControls->GetCharacterMovement();

	if (!IsValid(movement))
		return;

	mVelocity = movement->Velocity.Length();
	
	mAcceleration = movement->GetCurrentAcceleration().Length() > .1f;
	mIsInAir = movement->IsFalling();
}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UPlayerAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UPlayerAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!IsValid(mAttackMontage))
		return;

	if (mAttackState)
	{
		if (!Montage_IsPlaying(mAttackMontage))
		{
			Montage_SetPosition(mAttackMontage, 0.f);
			Montage_Play(mAttackMontage);
			Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);
		}
	}
	else
		mAttackCombo = true;

	mAttackState = true;
}

// Notifies
void UPlayerAnimInstance::AnimNotify_AttackCombo()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Combo"));
}

void UPlayerAnimInstance::AnimNotify_AttackComboEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("ComboEnd"));
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
}

void UPlayerAnimInstance::AnimNotify_AttackDisable()
{
}

void UPlayerAnimInstance::MontageEnd(UAnimMontage* montage, bool bInterrupted)
{
}
