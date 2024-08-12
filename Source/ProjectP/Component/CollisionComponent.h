// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"
#include "Components/ActorComponent.h"
#include "CollisionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	bool bIsCollisionEnable = false;
	UPROPERTY(VisibleAnywhere) TArray<AActor*> mHitActorArray;
	TObjectPtr<UStaticMeshComponent> mOwnerMeshComponent;

	// for trace
	FVector mStartLocation;
	FVector mEndLocation;
	TArray<FHitResult> mHitResultArray;
	TObjectPtr<AActor> mHitActor = nullptr;
	FCollisionQueryParams mQueryParam;
	bool bIsAnyCollide;
	float mHalfHeight;
	FQuat mDebugQuat = FQuat::Identity;

public:	
	// Sets default values for this component's properties
	UCollisionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION() void CollisionEnable();
	UFUNCTION() void CollisionDisable();
	UFUNCTION() void CollisionTrace();
	UFUNCTION() void ClearHitActors();

	void AddIgnoreActor(const AActor* actor);

	// getter
	TArray<AActor*> GetHitActorArray() const {return mHitActorArray;}
	bool GetIsCollisionEnable() const {return bIsCollisionEnable;}
};
