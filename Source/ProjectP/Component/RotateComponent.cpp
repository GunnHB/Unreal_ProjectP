// Fill out your copyright notice in the Description page of Project Settings.

#include "RotateComponent.h"

URotateComponent::URotateComponent()
{
}

void URotateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URotateComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float URotateComponent::GetAngle(const AActor* targetActor, bool ownerToTarget)
{
	// FVector targetLocation = targetActor->GetActorLocation();
	FVector targetLocation = targetActor->GetActorLocation();
	FVector ownerLocation = GetOwner()->GetActorLocation();

	// Z 축은 무시
	FVector targetVector = ownerToTarget ? GetVector(targetLocation, ownerLocation) : GetVector(ownerLocation, targetLocation) * FVector(1.f, 1.f, 0.f);
	FVector forwardVector = ownerToTarget ? GetOwner()->GetActorForwardVector() : targetActor->GetActorForwardVector();

	return GetAngle(forwardVector, targetVector);
}

float URotateComponent::GetAngleByDelta(const AActor* targetActor, bool ownerToTarget)
{
	return GetAngle(targetActor, ownerToTarget) * GetWorld()->GetDeltaSeconds();
}

float URotateComponent::GetAngleToTargetLocation(const FVector& targetLocation)
{
	FVector ownerLocation = GetOwner()->GetActorLocation();
	
	FVector targetVector = GetVector(targetLocation, ownerLocation) * FVector(1.f, 1.f, 0.f);
	FVector forwardVector = GetOwner()->GetActorForwardVector();

	return GetAngle(forwardVector, targetVector);
}

float URotateComponent::GetAngleToTargetLocationByDelta(const FVector& targetLocation)
{
	return GetAngleToTargetLocation(targetLocation) * GetWorld()->GetDeltaSeconds();
}

float URotateComponent::GetAngleToTargetForward(const FVector& targetForward)
{
	FVector tempTargetForward = targetForward;
	
	return GetAngle(GetOwner()->GetActorForwardVector(), tempTargetForward);
}

void URotateComponent::SetOwnerRotationByDelta(const FVector& targetLocation)
{
	float currentYaw = GetOwner()->GetActorRotation().Yaw;
	float deltaYaw = GetAngleToTargetLocationByDelta(targetLocation);

	GetOwner()->SetActorRelativeRotation(FRotator(0.f, currentYaw + deltaYaw, 0.f));
}

FVector URotateComponent::GetVector(const FVector& firstVector, const FVector& secondVector) const
{
	return firstVector - secondVector;
}

float URotateComponent::GetAngle(const FVector& forwardVector, FVector& targetVector)
{
	if(targetVector.Normalize())
	{
		float dotProduct = FVector::DotProduct(forwardVector, targetVector);		// 내적
		FVector crossProduct = FVector::CrossProduct(forwardVector, targetVector);	// 외적
		float angle = FMath::RadiansToDegrees(FMath::Acos(dotProduct));

		angle *= crossProduct.Z > 0 ? 1.f : -1.f;

		return angle;
	}

	return 0.f;
}
