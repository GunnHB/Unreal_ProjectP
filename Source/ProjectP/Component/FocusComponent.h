// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "Components/ActorComponent.h"
#include "FocusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UFocusComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	FHitResult mHitResult;
	FCollisionQueryParams mQueryParam;

	TObjectPtr<AActor> mTargetActor = nullptr;
	
public:
	UFocusComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void TryFocus(const FVector& forwardVector);
	void ResetTargetActor() {mTargetActor = nullptr;}

	// getter
	AActor* GetTargetActor() const {return mTargetActor;}

private:
	bool FindActor(const FVector& forwardVector);
	
#if ENABLE_DRAW_DEBUG
	void DrawWireCircleForDebug();
#endif
};
