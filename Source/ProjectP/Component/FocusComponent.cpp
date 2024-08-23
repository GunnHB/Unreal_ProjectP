// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusComponent.h"

#include "RotateComponent.h"

UFocusComponent::UFocusComponent()
{
	// 활성화돼야 tick 함수가 실행됨
	PrimaryComponentTick.bCanEverTick = true;
}

void UFocusComponent::BeginPlay()
{
	Super::BeginPlay();

	// 나는 무시
	mQueryParam.AddIgnoredActor(GetOwner());
}

void UFocusComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if ENABLE_DRAW_DEBUG
	DrawWireCircleForDebug();
#endif
}

void UFocusComponent::TryFocus(const FVector& forwardVector)
{
	FindActor(forwardVector);
}

bool UFocusComponent::FindActor(const FVector& forwardVector)
{
	FVector startLocation = GetOwner()->GetActorLocation() * FVector(1.f, 1.f, 0.f);
	FVector endLocation = startLocation + forwardVector * GameValue::GetEnableToFocusRange();

	float halfHeight = FVector::Dist(startLocation, endLocation) * .5f;
	
	bool bIsAnyDetect = GetWorld()->SweepSingleByChannel(mHitResult, startLocation, endLocation, FQuat::Identity, ECC_GameTraceChannel5, FCollisionShape::MakeSphere(GameValue::GetEnableToFocusRadius()), mQueryParam);

#if ENABLE_DRAW_DEBUG
	FColor drawColor = bIsAnyDetect ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), (startLocation + endLocation) * .5f, halfHeight, GameValue::GetEnableToFocusRadius(), FRotationMatrix::MakeFromZ(forwardVector).ToQuat(), drawColor, false, .018f);
#endif

	mTargetActor = bIsAnyDetect ? mHitResult.GetActor() : nullptr;

	return mTargetActor != nullptr;
}

#if ENABLE_DRAW_DEBUG
void UFocusComponent::DrawWireCircleForDebug()
{
	DrawDebugCircle(GetWorld(), GetOwner()->GetActorLocation() * FVector(1.f, 1.f, 0.f), GameValue::GetEnableToFocusRange(), 50, FColor(0.f, 0.f, 0.f), false, .015f, 0, 1.f, FVector::UnitX(), FVector::UnitY(), false);
}
#endif