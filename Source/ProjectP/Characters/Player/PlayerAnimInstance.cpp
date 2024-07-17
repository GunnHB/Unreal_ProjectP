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

	APlayerControls* pControl = Cast<APlayerControls>(TryGetPawnOwner());

	if (!IsValid(pControl))
		return;

	UCharacterMovementComponent* movement = Cast<UCharacterMovementComponent>(pControl->GetMovementComponent());

	if (!IsValid(movement))
		return;

	mSpeed = movement->Velocity.Size();
	mAcceleration = movement->GetCurrentAcceleration().Length() > 0.f;
	mIsInAir = movement->IsFalling();
	
	if (!mIsInAir)
		mPlayJumpAnim = false;
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

	// ��������Ʈ ���
	OnMontageEnded.AddDynamic(this, &UPlayerAnimInstance::MontageEnded);
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!IsValid(mAttackMontage) || mAttackSectionArray.IsEmpty())
		return;

	if (!mAttackState)
	{
		if (!Montage_IsPlaying(mAttackMontage))
		{
			Montage_SetPosition(mAttackMontage, 0.1f);
			Montage_Play(mAttackMontage);	
			Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);
		}

		mAttackState = true;
	}
	else
		mAttackCombo = true;
}

void UPlayerAnimInstance::MontageEnded(UAnimMontage* montage, bool bInterrupted)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Montage end"));

	mAttackState = false;
	mAttackCombo = false;
	mCurrentAttackSection = 0;
}

void UPlayerAnimInstance::PlayJumpAnim()
{
	mPlayJumpAnim = true;
}

void UPlayerAnimInstance::AnimNotify_Combo()
{
	if (!mAttackCombo)
		return;

	mCurrentAttackSection = (mCurrentAttackSection + 1) % mAttackSectionArray.Num();

	Montage_SetPosition(mAttackMontage, 0.1f);
	Montage_Play(mAttackMontage);
	Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);

	mAttackCombo = false;
}

void UPlayerAnimInstance::AnimNotify_ResetCombo()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Combo End"));

	if (!mAttackCombo)
	{
		mAttackState = false;
		mCurrentAttackSection = 0;
	}
}