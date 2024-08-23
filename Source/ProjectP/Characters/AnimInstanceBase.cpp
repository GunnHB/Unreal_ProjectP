// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceBase.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mPawn = TryGetPawnOwner();

	if(IsValid(mPawn))
		mPawnMovement = mPawn->GetMovementComponent();
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(IsValid(mPawnMovement))
		mSpeed = mPawnMovement->GetMaxSpeed();
}

void UAnimInstanceBase::PlayAttackMontage(TArray<UAnimMontage*> montageArray, int32 attackIndex, bool randomAttack)
{
	int32 currIndex = randomAttack ? FMath::RandRange(0, montageArray.Num() - 1) : attackIndex;
	UAnimMontage* playAttackMontage = montageArray[currIndex];

	if(!IsValid(playAttackMontage))
		return;
	
	if(!Montage_IsPlaying(playAttackMontage))
	{
		Montage_SetPosition(playAttackMontage, 0.f);
		Montage_Play(playAttackMontage);
	}	
}