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
	float _movementSpeed = 0;

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
	float GetMovementSpeed() { return _movementSpeed; }
	void SetMovementSpeed(const float& value) { _movementSpeed = value; }
};
