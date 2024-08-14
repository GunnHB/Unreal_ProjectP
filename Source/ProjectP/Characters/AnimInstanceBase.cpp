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
