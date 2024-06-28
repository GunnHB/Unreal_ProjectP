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

	OnMontageEnded.AddDynamic(this, &UPlayerAnimInstance::MontageEnd);
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!IsValid(mAttackMontage))
		return;

	if (!mAttackState)
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
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Combo"));

	//// 콤보 공격 가능
	//if (mAttackCombo)
	//{
	//	mCurrentAttackSection = (mCurrentAttackSection + 1) % mAttackSectionArray.Num();

	//	// 다음 공격 애니 재생
	//	Montage_SetPosition(mAttackMontage, 0.f);
	//	Montage_Play(mAttackMontage);
	//	Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);

	//	mAttackCombo = false;
	//}
}

void UPlayerAnimInstance::AnimNotify_AttackComboEnd()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("ComboEnd"));

	//if (!IsValid(mAttackRecoveryMontage))
	//	return;

	//if (mCurrentAttackSection < mAttackSectionArray.Num() - 1)
	//{
	//	Montage_SetPosition(mAttackRecoveryMontage, 0.f);
	//	Montage_Play(mAttackRecoveryMontage);
	//	Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);
	//}
	//else
	//{
	//	mAttackCombo = false;
	//	mAttackState = false;

	//	mCurrentAttackSection = 0;
	//}

	if (mCurrentAttackSection % mAttackSectionArray.Num() == mAttackSectionArray.Num() - 1)
		ResetDatas();

	if (mAttackCombo)
	{
		mCurrentAttackSection = (mCurrentAttackSection + 1) % mAttackSectionArray.Num();

		// 다음 공격 애니 재생
		Montage_SetPosition(mAttackMontage, 0.f)	;
		Montage_Play(mAttackMontage);
		Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);

		mAttackCombo = false;
	}
	else if (mCurrentAttackSection < mAttackSectionArray.Num() - 1)
	{
		if (!IsValid(mAttackRecoveryMontage))
			return;

		Montage_SetPosition(mAttackRecoveryMontage, 0.f);
		Montage_Play(mAttackRecoveryMontage);
		Montage_JumpToSection(mAttackSectionArray[mCurrentAttackSection]);
	}
	else
		ResetDatas();

}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	//APlayerControls* playerCharacter = Cast<APlayerControls>(TryGetPawnOwner());

	//if (IsValid(playerCharacter))
	//	playerCharacter->AttackEnable();
}

void UPlayerAnimInstance::AnimNotify_AttackDisable()
{
	//APlayerControls* playerCharacter = Cast<APlayerControls>(TryGetPawnOwner());

	//if (IsValid(playerCharacter))
		//playerCharacter->AttackDisable();
}

void UPlayerAnimInstance::MontageEnd(UAnimMontage* montage, bool bInterrupted)
{
	if (montage == mAttackRecoveryMontage)
		ResetDatas();
}
