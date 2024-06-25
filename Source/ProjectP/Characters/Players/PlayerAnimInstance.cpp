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

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, FString::Printf(TEXT("%f"), movement->Velocity.Length()));
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
