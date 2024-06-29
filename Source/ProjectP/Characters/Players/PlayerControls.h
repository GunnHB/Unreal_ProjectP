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

	TObjectPtr<class UPlayerAnimInstance_SS> mAnimInstance = nullptr;

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
	void MovementAction(const FInputActionValue& value);
	void MovementStopAction(const FInputActionValue& value);
	void CameraMovementAction(const FInputActionValue& value);
	void AttackAction(const FInputActionValue& value);
	void JumpAction(const FInputActionValue& value);

protected:
	virtual void NormalAttack();

public:
	virtual void AttackEnable();
	virtual void AttackDisable();

public:
	// getter
	FVector GetThisInputAxis() { return mInputAxis; }

private:
	void AdjustCamRotation(FRotator& rotator)
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

	void AdjustActorRotation()
	{
		FVector direction = mInputAxis.GetSafeNormal();

		// 입력 방향 + 카메라 방향
		float targetAngle = FMath::Atan2(direction.X, direction.Y) * FMathf::RadToDeg + mSpringArm->GetRelativeRotation().Yaw;

		// 값 보정
		if (targetAngle < -180.f)
			targetAngle = 360 + targetAngle;
		else if (targetAngle > 180.f)
			targetAngle = targetAngle - 360.f;

		FRotator targetRotation = FRotator(0.f, targetAngle, 0.f);

		// 회전 보간 (현재 회전 값, 목표 회전 값, deltatime, 회전 속도)
		FRotator rotation = FMath::RInterpTo(GetActorRotation(), targetRotation, GetWorld()->GetDeltaSeconds(), 10.f);

		SetActorRotation(rotation);
	}
};
