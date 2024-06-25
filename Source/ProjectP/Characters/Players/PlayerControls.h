// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"

#include "../CharacterControls.h"
#include "PlayerControls.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APlayerControls : public ACharacterControls
{
	GENERATED_BODY()
	
public:
	APlayerControls();

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mArm = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera = nullptr;

	TObjectPtr<class UPlayerAnimInstance> mAnimInstance;

private:
	FRotator mCamRotator = FRotator::ZeroRotator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void InitAssets() override;
	virtual void InitCompoValues() override;

protected:
	void MovementAction(const FInputActionValue& value);
	void CameraMovementAction(const FInputActionValue& value);

private:
	void AdjustCamRotator(FRotator& rotator)
	{
		if (rotator.Yaw < -180.f)
			rotator.Yaw = 360.f + rotator.Yaw;
		else if (rotator.Yaw > 180.f)
			rotator.Yaw = rotator.Yaw - 360.f;

		if (rotator.Pitch < -60.f)
			rotator.Pitch = -60.f;
		else if (rotator.Pitch > 20.f)
			rotator.Pitch = 20.f;
	}
};