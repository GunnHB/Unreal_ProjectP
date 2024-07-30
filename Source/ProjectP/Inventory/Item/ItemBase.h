// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class PROJECTP_API AItemBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> mCapsule = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> mStaticMesh = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
