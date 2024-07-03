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

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mSpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	// 클래스의 전방선언
	// 다른 컴포넌트들도 tobjectptr로 선언할 수 있다.
	// 잠깐 알아보니 언리얼에서는 이 방식을 권장한다고 함
	TObjectPtr<class UPlayerAnimInstance> mAnimInstance;

private:
	FVector mInputVector;
	FRotator mCamRotator;

public:
	// Sets default values for this character's properties
	APlayerControls();

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
	virtual void InitComponentsValue();

private:
	// 액션 바인딩
	void BindInputActions(class UInputComponent* PlayerInputComponent);
	// 맵핑
	void MappingContext();

protected:
	void MovementAction(const FInputActionValue& value);
	void MovementStopAction(const FInputActionValue& value);
	void CameraMovementAction(const FInputActionValue& value);
	void JumpAction(const FInputActionValue& value);
	void AttackAction(const FInputActionValue& value);

private:
	void AdjustCameraRotation();
	void AdjustActorRotation();

protected:
	void NormalAttack();
};
