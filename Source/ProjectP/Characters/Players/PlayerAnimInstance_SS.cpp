// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance_SS.h"

#include "PlayerControls.h"

void UPlayerAnimInstance_SS::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance_SS::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 플레이어 객체 가져오기
	APlayerControls* pControls = Cast<APlayerControls>(TryGetPawnOwner());

	if (!IsValid(pControls))
		return;

	UCharacterMovementComponent* movement = pControls->GetCharacterMovement();

	if (!IsValid(movement))
		return;

	mVelocity = movement->Velocity.Size();
	mAcceleration = movement->GetCurrentAcceleration().Size() > .1f;

	mIsInAir = movement->IsFalling();
	
	if (!mIsInAir)
		mJump = false;
}

void UPlayerAnimInstance_SS::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UPlayerAnimInstance_SS::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UPlayerAnimInstance_SS::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UPlayerAnimInstance_SS::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance_SS::PlayAttackMontage()
{
	if (!IsValid(mAttackMontage))
		return;
	// 
	//if (!Montage_IsPlaying(mAttackMontage))
	//{
	//	Montage_SetPosition(mAttackMontage, 0.f);
	//	Montage_Play(mAttackMontage);
	//	Montage_JumpToSection(mAttackSectionArray[mCurrentAttckSection]);
	//}
	//// 공중 공격
	//if (mIsInAir)
	//{
	//	if (!Montage_IsPlaying(mAttackMontage))
	//	{
	//		Montage_SetPosition(mAttackMontage, 0.f);
	//		Montage_Play(mAttackMontage);
	//		Montage_JumpToSection(mAttackSectionArray[mCurrentAttckSection]);
	//	}
	//}
	//// 일반 공격
	//else
	//{
	//	if (!mAttackState)
	//	{
	//		if (!Montage_IsPlaying(mAttackMontage))
	//		{
	//			Montage_SetPosition(mAttackMontage, 0.f);
	//			Montage_Play(mAttackMontage);
	//			Montage_JumpToSection(mAttackSectionArray[mCurrentAttckSection]);
	//		}
	//	}
	//	else
	//		mAttackCombo = true;

	//	mAttackState = true;
	//}
}

void UPlayerAnimInstance_SS::AnimNotify_Combo()
{

}

void UPlayerAnimInstance_SS::AnimNotify_ResetCombo()
{

}

void UPlayerAnimInstance_SS::MontageEnd(UAnimMontage* montage, bool bInterrupted)
{
}
