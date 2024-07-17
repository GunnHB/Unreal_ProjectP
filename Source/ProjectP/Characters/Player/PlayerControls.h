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
	// 언리얼에서는 이 방식을 권장한다고 함
	TObjectPtr<class UPlayerAnimInstance> mAnimInstance;

	bool bFocus = false;

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
	virtual void InitAssets();												// 에셋 초기화
	virtual void InitComponentsValue();										// 컴포넌트 값 초기화

	// 액션
	void MovementAction(const FInputActionValue& value);					// 이동
	void MovementStopAction(const FInputActionValue& value);				// 이동 취소
	void CameraMovementAction(const FInputActionValue& value);				// 카메라 이동
	void JumpAction(const FInputActionValue& value);						// 점프
	void AttackAction(const FInputActionValue& value);						// 공격
	void SprintAction(const FInputActionValue& value);						// 달리기
	void FocusAction(const FInputActionValue& value);						// 포커싱

	void NormalAttack();													// 공격

private:
	void BindInputActions(class UInputComponent* PlayerInputComponent);		// 액션 바인딩
	void MappingContext();													// 맵핑

	void AdjustCameraRotation();											// 카메라 회전 조정
	void AdjustActorRotation();												// 캐릭터 회전 조정
};
