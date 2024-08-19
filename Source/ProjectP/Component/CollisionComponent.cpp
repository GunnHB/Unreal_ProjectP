// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionComponent.h"

#include "../Interface/CollisionEnable.h"
#include "../Interface/Damageable.h"

UCollisionComponent::UCollisionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	ICollisionEnable* collision = Cast<ICollisionEnable>(GetOwner());

	if(collision)
		mOwnerMeshComponent = collision->GetMesh();

	// camera shake
	static ConstructorHelpers::FClassFinder<UCameraShakeBase>
		mCamShakeAsset(TEXT("/Script/Engine.Blueprint'/Game/08_BluePrint/BP_CameraShakeByDamage.BP_CameraShakeByDamage_C'"));

	if(mCamShakeAsset.Succeeded())
		mCameraShakeClass = mCamShakeAsset.Class;
}

void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	
	DrawDebugCapsule(GetWorld(), (mStartLocation + mEndLocation) * .5f, mHalfHeight, 7.f, mDebugQuat, drawColor, false, -1.f);
#endif

	for(FHitResult hit : mHitResultArray)
	{
		if(!mHitActorArray.Contains(hit.GetActor()))
		{
			mHitActorArray.Add(hit.GetActor());

			IDamageable* takerDamageable = Cast<IDamageable>(hit.GetActor());

			if(takerDamageable != nullptr)
			{
				takerDamageable->TakeDamage(Cast<APawn>(mOwnerActor));
				takerDamageable->SpawnEmitter(hit);

				if(IsValid(mCameraShakeClass))
					GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(mCameraShakeClass);
			}
		}
	}
}

void UCollisionComponent::ClearHitActors()
{
	mHitActorArray.Empty();
}

void UCollisionComponent::AddIgnoreActor(AActor* actor)
{
	mOwnerActor = actor;
	
	mQueryParam.AddIgnoredActor(actor);
}

