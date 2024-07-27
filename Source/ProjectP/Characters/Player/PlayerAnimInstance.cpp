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

	SetAimOffset(pControl);
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

void UPlayerAnimInstance::PlayJumpAnim()
{
	mPlayJumpAnim = true;
}

void UPlayerAnimInstance::SetAimOffset(APlayerControls* pControl)
{
	FVector camVector = pControl->GetCameraFowradVector();
	camVector.Normalize();

	// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("x->%f y->%f"), camVector.X, camVector.Y));
}