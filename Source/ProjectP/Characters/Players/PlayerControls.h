// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"

#include "../../System/GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerControls.generated.h"

UCLASS()
class PROJECTP_API APlayerControls : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerControls();

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera = nullptr;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mSpringArm = nullptr;

	FRotator mCamRotator = FRotator::ZeroRotator;
	FVector mInputAxis = FVector::ZeroVector;

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
	virtual void InitComponentValues();

protected:
	void Movement(const FInputActionValue& value);
	void MovementStop(const FInputActionValue& value);
	void CameraMovement(const FInputActionValue& value);
	void Attack(const FInputActionValue& value);
	void Jump(const FInputActionValue& value);

protected:
	virtual void NormalAttack();

public:
	virtual void AttackEnable();
	virtual void AttackDisable();

public:
	// getter
	FVector GetThisInputAxis() { return mInputAxis; }

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

	void GetTargetAngle()
	{
		FVector direction = mInputAxis.GetSafeNormal();

		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("x->%f, y->%f"), direction.X, direction.Y));

		float targetAngle = FMath::Atan2(direction.X, direction.Y) * FMathf::RadToDeg;

		if (targetAngle < -180.f)
			targetAngle = 360 + targetAngle;
		else if (targetAngle > 180.f)
			targetAngle = targetAngle - 360.f;

		SetActorRotation(FRotator(0.f, targetAngle, 0.f));
	}
};
