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

	mDegreee = mPlayer->GetInputDegree();
	mLastDegree = mPlayer->GetLastDegree();
	mDamageDegree = mPlayer->GetDamageDegree();
	
	mAimOffsetX = mPlayer->GetAnimOffsetX();
	mSpeed = mPlayerMovement->Velocity.Size();
	mAcceleration = mPlayerMovement->GetCurrentAcceleration().Length() > 0.f;
	mIsInAir = mPlayerMovement->IsFalling();
	
	bInputForMovement = mPlayer->GetInputVector().Size() > 0.01f;
	bIsDodge = mPlayer->GetCombatComponent()->GetIsDodge();
	bTakeDamage = mPlayer->GetCombatComponent()->GetTakeDamage();

	if(!mPlayer->GetCombatComponent()->IsMainWeaponNull())
	{
		AWeaponBase* weapon = mPlayer->GetCombatComponent()->GetMainWeapon();

		if(weapon->GetWeaponData()->type == EWeaponType::Sword)
			bIsOneHandWeapon = Cast<AWeaponSword>(weapon)->GetSwordData()->type == ESwordType::OneHand;

		bIsEquipped = mPlayer->GetCombatComponent()->GetMainWeapon()->GetIsEquipped();
	}
	else
	{
		bIsOneHandWeapon = true;
		bIsEquipped = false;
	}
	
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
	if(mPlayer->GetCombatComponent()->IsMainWeaponNull())
		return;

	AWeaponBase* tempWeapon = mPlayer->GetCombatComponent()->GetMainWeapon();

	if(tempWeapon->GetWeaponData()->type == EWeaponType::Sword)
		mDrawWeaponMontage = Cast<AWeaponSword>(tempWeapon)->GetSwordData()->montage_draw;

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
	if(mPlayer->GetCombatComponent()->IsMainWeaponNull())
		return;

	AWeaponBase* tempWeapon = mPlayer->GetCombatComponent()->GetMainWeapon();

	if(tempWeapon->GetWeaponData()->type == EWeaponType::Sword)
		mSheathWeaponMontage = Cast<AWeaponSword>(tempWeapon)->GetSwordData()->montage_sheath;

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
	if(mPlayer->GetCombatComponent()->GetMainWeapon()->IsA(AWeaponSword::StaticClass()))
	{
		AWeaponSword* sword = Cast<AWeaponSword>(mPlayer->GetCombatComponent()->GetMainWeapon());

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

void UPlayerAnimInstance::SetTakeDamageDegree()
{
	
}

void UPlayerAnimInstance::PerformPlayMontage(UAnimMontage* montage)
{
	if(!IsValid(montage))
		return;
	
	if(!Montage_IsPlaying(montage))
	{
		Montage_SetPosition(montage, 0.f);
		Montage_Play(montage);
	}
}

void UPlayerAnimInstance::AnimNotify_LandEnd()
{
	// 플래그 변환
	bIsLandingAnimEnd = true;
}
