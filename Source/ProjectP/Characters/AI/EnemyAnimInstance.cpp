// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"

#include "AIPawn.h"
#include "../../Component/EnemyMovementComponent.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(IsValid(GetThisPawn()))
		mAIPawn = Cast<AAIPawn>(GetThisPawn());

	if(IsValid(GetThisPawnMovement()))
		mAIMovement = Cast<UEnemyMovementComponent>(GetThisPawnMovement());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
