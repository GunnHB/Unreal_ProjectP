// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CapsuleComponent.h"

#include "../System/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "CharacterControls.generated.h"

UCLASS()
class PROJECTP_API ACharacterControls : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharacterControls();

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mSkeletalMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* mCapsule = nullptr;

private:
	float mMovementSpeed = 0.f;
	float mVelocity = 0.f;
	float mAcceleration = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void InitAssets();
	virtual void InitCompoValues();

protected:
	// getter
	float GetMovementSpeed() { return mMovementSpeed; }
	float GetUserVelocity() { return mVelocity; }
	float GetUserAcceleration() { return mAcceleration; }

	// setter
	void SetMovementSpeed(const float& value) { mMovementSpeed = value; }
	void SetUserVelocity(const float& value) { mVelocity = value; }
	void SetUserAcceleration(const float& value) { mAcceleration = value; }
};
