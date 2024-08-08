// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "PlayerControls.h"
#include "ProjectP/Inventory/Item/Weapon/WeaponSword.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mPlayer = Cast<APlayerControls>(TryGetPawnOwner());

	if(!IsValid(mPlayer))
		return;

	mPlayerMovement = Cast<UCharacterMovementComponent>(mPlayer->GetMovementComponent());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if(!IsValid(mPlayerMovement))
		return;
	
	mSpeed = mPlayerMovement->Velocity.Size();
	mAcceleration = mPlayerMovement->GetCurrentAcceleration().Length() > 0.f;
	mIsInAir = mPlayerMovement->IsFalling();
	bInputForMovement = mPlayer->GetInputVector().Size() > 0.01f;

	if(mPlayer->GetCombat()->GetMainWeapon() != nullptr)
	{
		bIsOneHandWeapon = Cast<AWeaponSword>(mPlayer->GetCombat()->GetMainWeapon())->GetSwordData()->type == ESwordType::OneHand;
		bIsEquipped = mPlayer->GetCombat()->GetMainWeapon()->GetIsEquipped();
	}
	else
	{
		bIsOneHandWeapon = true;
		bIsEquipped = false;
	}
	
	// if (!mIsInAir)
	// 	mPlayJumpAnim = false;
	// else
	// 	bIsLandingAnimEnd = false;

	if(mIsInAir)
		bIsLandingAnimEnd = false;
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

void UPlayerAnimInstance::PlayDrawWeaponMontage()
{
	if(mPlayer->GetCombat()->GetMainWeapon() == nullptr)
		return;

	if(mPlayer->GetCombat()->GetMainWeapon()->IsA(AWeaponSword::StaticClass()))
	{
		AWeaponSword* sword = Cast<AWeaponSword>(mPlayer->GetCombat()->GetMainWeapon());

		if(IsValid(sword))
			mDrawWeaponMontage = sword->GetSwordData()->montage_draw;
	}
	
	if(!IsValid(mDrawWeaponMontage))
		return;
	
	if(!Montage_IsPlaying(mDrawWeaponMontage))
	{
		Montage_SetPosition(mDrawWeaponMontage, 0.f);
		Montage_Play(mDrawWeaponMontage);
	}
}

void UPlayerAnimInstance::PlaySheathWeaponMontage()
{
	if(mPlayer->GetCombat()->GetMainWeapon() == nullptr)
		return;

	if(mPlayer->GetCombat()->GetMainWeapon()->IsA(AWeaponSword::StaticClass()))
	{
		AWeaponSword* sword = Cast<AWeaponSword>(mPlayer->GetCombat()->GetMainWeapon());

		if(IsValid(sword))
			mSheathWeaponMontage = sword->GetSwordData()->montage_sheath;
	}

	if(!IsValid(mSheathWeaponMontage))
		return;
	
	if(!Montage_IsPlaying(mSheathWeaponMontage))
	{
		Montage_SetPosition(mSheathWeaponMontage, 0.f);
		Montage_Play(mSheathWeaponMontage);
	}
}

void UPlayerAnimInstance::PlayAttackMontage(int32 attackIndex, bool randomIndex)
{
	if(mPlayer->GetCombat()->GetMainWeapon()->IsA(AWeaponSword::StaticClass()))
	{
		AWeaponSword* sword = Cast<AWeaponSword>(mPlayer->GetCombat()->GetMainWeapon());

		if(IsValid(sword))
		{
			TArray<UAnimMontage*> montageArray = sword->GetSwordData()->montage_attack_array;

			mAttackMontage = randomIndex ? montageArray[FMath::RandRange(0, montageArray.Num() - 1)] : montageArray[attackIndex];
		}
	}

	if(!IsValid(mAttackMontage))
		return;

	if(!Montage_IsPlaying(mAttackMontage))
	{
		Montage_SetPosition(mAttackMontage, 0.f);
		Montage_Play(mAttackMontage);
	}
}

void UPlayerAnimInstance::PlayDodgeMontage(bool isRoll)
{
	




	
	// UAnimMontage* tempMontage = isRoll ? mRollMontageMap[swordType] : mDodgeMontageMap[swordType];
	//
	// if(tempMontage == nullptr)
	// 	return;
	//
	// if(!Montage_IsPlaying(tempMontage))
	// {
	// 	Montage_SetPosition(tempMontage, 0.f);
	// 	Montage_Play(tempMontage);
	// }
}

void UPlayerAnimInstance::AnimNotify_LandEnd()
{
	// 플래그 변환
	bIsLandingAnimEnd = true;
}
