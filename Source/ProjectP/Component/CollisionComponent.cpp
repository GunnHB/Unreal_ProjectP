// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionComponent.h"

#include "../Interface/CollisionEnable.h"

UCollisionComponent::UCollisionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	ICollisionEnable* collision = Cast<ICollisionEnable>(GetOwner());

	if(collision)
		mOwnerMeshComponent = collision->GetMesh();
}

void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bIsCollisionEnable)
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
		mDebugQuat = collision->GetQuat();
	
	DrawDebugCapsule(GetWorld(), (mStartLocation + mEndLocation) * .5f, mHalfHeight, 7.f, mDebugQuat, drawColor, false, .02f);
#endif

	for(FHitResult hit : mHitResultArray)
	{
		mLastHit = hit;
		
		if(!mHitActorArray.Contains(mLastHit.GetActor()))
		{
			mHitActor = mLastHit.GetActor();

			mHitActorArray.Add(mHitActor);
		}
	}
}

void UCollisionComponent::ClearHitActors()
{
	mHitActorArray.Empty();
}

void UCollisionComponent::AddIgnoreActor(const AActor* actor)
{
	mQueryParam.AddIgnoredActor(actor);
}

