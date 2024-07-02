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

	mVelocity = movement->Velocity.Size();
	mIsMove = mVelocity > 0.1f;
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

	// 델리게이트 등록
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
			Montage_SetPosition(mAttackMontage, 0.1f);							// 처음으로 세팅
			Montage_Play(mAttackMontage);										// 몽타주 재생
			Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);	// 첫 섹션 재생됨
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
