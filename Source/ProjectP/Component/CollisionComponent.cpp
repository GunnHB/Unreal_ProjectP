// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionComponent.h"

#include "../Interface/CollisionEnable.h"

// Sets default values for this component's properties
UCollisionComponent::UCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	ICollisionEnable* collisionEnable = Cast<ICollisionEnable>(GetOwner());

	if(collisionEnable)
		mOwnerMeshComponent = collisionEnable->GetMesh();
}


// Called when the game starts
void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CollisionTrace();
}

void UCollisionComponent::CollisionEnable()
{
	ClearHitActors();
	
	bIsCollisionEnable = true;
}

void UCollisionComponent::CollisionDisable()
{
	bIsCollisionEnable = false;
}

void UCollisionComponent::CollisionTrace()
{
	bIsAnyCollide = GetWorld()->SweepMultiByChannel(mHitResultArray, mStartLocation, mEndLocation, FQuat::Identity, ECC_GameTraceChannel4, FCollisionShape::MakeSphere(20.f), mQueryParam);

	mStartLocation = mOwnerMeshComponent->GetSocketLocation(GameValue::GetCollisionStartSocketName());
	mEndLocation = mOwnerMeshComponent->GetSocketLocation(GameValue::GetCollisionEndSocketName());

	mHalfHeight = FVector::Distance(mStartLocation, mEndLocation) * .5f;

#if ENABLE_DRAW_DEBUG
	FColor drawColor = bIsAnyCollide ? FColor::Red : FColor::Green;

	ICollisionEnable* collision = Cast<ICollisionEnable>(GetOwner());

	if(collision != nullptr)
		mQuat = collision->GetQuat();
	
	DrawDebugCapsule(GetWorld(), (mStartLocation + mEndLocation) * .5f, mHalfHeight, 7.f, mQuat, drawColor, false, .02f);
#endif
}

void UCollisionComponent::ClearHitActors()
{
	mHitActorArray.Empty();
}

