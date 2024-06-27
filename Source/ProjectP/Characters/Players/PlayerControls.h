// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"

//#include "CoreMinimal.h"
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

	TObjectPtr<class UPlayerAnimInstance> mAnimInstance;

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
	virtual void InitAssets();
	virtual void InitComponentValues();

protected:
	void MovementAction(const FInputActionValue& value);
	void CameraMovementAction(const FInputActionValue& value);
	void AttackAction(const FInputActionValue& value);
	void JumpAction(const FInputActionValue& value);

protected:
	virtual void NormalAttack();

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

	float TargetAngle(const FVector& direction)
	{
		FVector targetDirection = (direction - GetActorLocation()).GetSafeNormal();

		return FMath::Atan2(targetDirection.X, targetDirection.Z) * FMathf::RadToDeg + mSpringArm->GetRelativeRotation().Pitch;
	}
};
