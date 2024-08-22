// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "Components/ActorComponent.h"
#include "RotateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API URotateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URotateComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	float GetAngle(const AActor* targetActor, bool ownerToTarget = true);
	float GetAngleByDelta(const AActor* targetActor, bool ownerToTarget = true);
	float GetAngleToTargetLocation(const FVector& targetLocation);
	float GetAngleToTargetLocationByDelta(const FVector& targetLocation);
	float GetAngleToTargetForward(const FVector& targetForward);

	void SetOwnerRotationByDelta(const FVector& targetLocation);

private:
	FVector GetVector(const FVector& firstVector, const FVector& secondVector) const;
	float GetAngle(const FVector& forwardVector, FVector& targetVector);
};
