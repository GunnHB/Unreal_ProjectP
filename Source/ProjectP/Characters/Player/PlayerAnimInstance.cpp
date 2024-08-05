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
		bIsEquipped = mPlayer->GetCombat()->GetMainWeapon()->IsEquipped();
	}
	else
	{
		bIsOneHandWeapon = true;
		bIsEquipped = false;
	}
	
	if (!mIsInAir)
		mPlayJumpAnim = false;
	else
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

		if(sword != nullptr)
			mDrawWeaponMontage = sword->GetSwordData()->montage_draw;
	}
	
	if(!IsValid(mDrawWeaponMontage))
		return;
	
	if(!Montage_IsPlaying(mDrawWeaponMontage) && !mPlayDrawWeaponAnim)
	{
		mPlayDrawWeaponAnim = true;
		
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

		if(sword != nullptr)
			mSheathWeaponMontage = sword->GetSwordData()->montage_sheath;
	}

	if(!IsValid(mSheathWeaponMontage))
		return;
	
	if(!Montage_IsPlaying(mSheathWeaponMontage) && !mPlaySheathWeaponAnim)
	{
		mPlaySheathWeaponAnim = true;
		
		Montage_SetPosition(mSheathWeaponMontage, 0.f);
		Montage_Play(mSheathWeaponMontage);
	}
}

void UPlayerAnimInstance::AnimNotify_DrawWeapon()
{
	mPlayer->GetCombat()->GetMainWeapon()->OnEquip();
	
	// 플래그 변환
	mPlayDrawWeaponAnim = false;
}

void UPlayerAnimInstance::AnimNotify_SheathWeapon()
{
	mPlayer->GetCombat()->GetMainWeapon()->OnUnequip();

	// 플래그 변환
	mPlaySheathWeaponAnim = false;
}

void UPlayerAnimInstance::AnimNotify_LandEnd()
{
	// 플래그 변환
	bIsLandingAnimEnd = true;
}
