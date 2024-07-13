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

	// Ŭ������ ���漱��
	// �ٸ� ������Ʈ�鵵 tobjectptr�� ������ �� �ִ�.
	// �𸮾󿡼��� �� ����� �����Ѵٰ� ��
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
	virtual void InitAssets();												// ���� �ʱ�ȭ
	virtual void InitComponentsValue();										// ������Ʈ �� �ʱ�ȭ

	// �׼�
	void MovementAction(const FInputActionValue& value);					// �̵�
	void MovementStopAction(const FInputActionValue& value);				// �̵� ���
	void CameraMovementAction(const FInputActionValue& value);				// ī�޶� �̵�
	void JumpAction(const FInputActionValue& value);						// ����
	void AttackAction(const FInputActionValue& value);						// ����
	void SprintAction(const FInputActionValue& value);						// �޸���
	void FocusAction(const FInputActionValue& value);						// ��Ŀ��

	void NormalAttack();													// ����

private:
	void BindInputActions(class UInputComponent* PlayerInputComponent);		// �׼� ���ε�
	void MappingContext();													// ����

	void AdjustCameraRotation();											// ī�޶� ȸ�� ����
	void AdjustActorRotation();												// ĳ���� ȸ�� ����
};
