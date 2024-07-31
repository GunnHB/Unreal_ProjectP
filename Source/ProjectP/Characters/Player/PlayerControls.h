// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "../../Interface/Interactable.h"

#include "../../System/GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerControls.generated.h"

UCLASS()
class PROJECTP_API APlayerControls : public ACharacter, public IInteractable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* mCamera;

	// 클래스의 전방선언
	// 다른 컴포넌트들도 tobjectptr로 선언할 수 있다.
	// UE5에서는 이 방식을 권장한다고 함
	TObjectPtr<class UPlayerAnimInstance> mAnimInstance;
	
	// for inventory
	TObjectPtr<class UInventoryWidget> mInventoryWidget;
	TSubclassOf<UInventoryWidget> mInventoryWidgetClass;
	bool mInventoryOpen = false;								// ui 종료되고 바로 실행되는 현상 방지위한 플래그

	// playerData
	TObjectPtr<class UPlayerData> mPlayerData = nullptr;

	// weapon
	TObjectPtr<class AWeaponItem> mMainWeapon = nullptr;
	

private:
	FVector mInputVector;
	FRotator mCamRotator;

	// for trace
	FVector mTraceStartPoint;
	FVector mTraceEndPoint;
	FHitResult mHitResult;
	FCollisionQueryParams mQueryParam;
	bool bEnableToInteract;

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
	
	// getter
	FVector GetCameraFowradVector() const {return mCamera->GetForwardVector();}
	UPlayerData* GetThisPlayerData() const {return mPlayerData;}
	AWeaponItem* GetMainWeaponItem() const {return mMainWeapon;}
	
	bool AddMoney(const FMoney* moneyData);

	virtual void Interact() override;

protected:
	void InitAssets();														// 에셋 초기화
	void InitComponentsValue();												// 컴포넌트 값 초기화

	// 액션
	void MovementAction(const FInputActionValue& value);					// 이동
	void MovementStopAction(const FInputActionValue& value);				// 이동 취소
	void CameraMovementAction(const FInputActionValue& value);				// 카메라 이동
	void JumpAction(const FInputActionValue& value);						// 점프
	void AttackAction(const FInputActionValue& value);						// 공격
	void SprintAction(const FInputActionValue& value);						// 달리기
	void FocusAction(const FInputActionValue& value);						// 포커싱
	void DrawWeaponAction(const FInputActionValue& value);					// 무기 장비
	void InteractAction(const FInputActionValue& value);					// 상호작용

	void InventoryAction(const FInputActionValue& value);					// 인벤토리 on / off

	void NormalAttack();													// 공격

private:
	void BindInputActions(class UInputComponent* PlayerInputComponent);		// 액션 바인딩
	void MappingContext() const;											// 맵핑

	void AdjustCameraRotation();											// 카메라 회전 조정
	void AdjustActorRotation();												// 캐릭터 회전 조정
	
	void DrawArrow();

	void TraceForInteractable(float deltaTime);

	void SpawnWeapon();
};
