// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"

#include "../../System/GameInfo.h"

#include "../../Interface/Combatable.h"
#include "../../Interface/Damageable.h"
#include "../../Interface/PickupEnable.h"

#include "GameFramework/Character.h"
#include "PlayerControls.generated.h"

class AItemBase;

UCLASS()
class PROJECTP_API APlayerControls : public ACharacter, public ICombatable, public IDamageable, public IPickupEnable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<USpringArmComponent> mSpringArm;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UCameraComponent> mCamera;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UCombatComponent> mCombat;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UStateManageComponent> mStateManage;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class URotateComponent> mRotate;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UFocusComponent> mFocus;
	
	TObjectPtr<class UPlayerAnimInstance> mAnimInstance;
	
	// for inventory
	TObjectPtr<class UInventoryWidget> mInventoryWidget;
	TSubclassOf<UInventoryWidget> mInventoryWidgetClass;
	bool mInventoryOpen = false;								// ui 종료되고 바로 실행되는 현상 방지위한 플래그
	
	TObjectPtr<class UPlayerStat> mPlayerStat = nullptr;

	ECharacterMovementType mCurrentMovementType = ECharacterMovementType::None;

private:
	FVector mInputVector;
	FVector mLastInputVector;
	FRotator mCamRotator;

	// for trace channel
	FVector mTraceStartPoint;
	FVector mTraceEndPoint;
	FHitResult mHitResult;
	FCollisionQueryParams mQueryParam;
	bool bEnableToInteract;
	
	bool bIsFocusing = false;				// focus 플래그

	float mDamageDegree = 0.f;
	
	FTimerHandle mHitStopTimeHandle;
	FTimerHandle mAttackTimeHandle;

public:
	APlayerControls();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	// getter
	FVector GetInputVector() const {return mInputVector;}
	UPlayerStat* GetThisPlayerStat() const {return mPlayerStat;}
	
	float GetInputDegree() const;
	float GetLastDegree() const;
	float GetAimOffsetX() const;

	float GetDamageDegree() const {return mDamageDegree;}

	ECharacterMovementType GetCurrentMovementType() const {return mCurrentMovementType;}

	// setter
	void SetDamageDegree(const AActor* hitter);
	void SetCurrentMovementType(const ECharacterMovementType type);
	void SetMovementSpeed();

	bool AddMoney(const FMoney* moneyData);

	// icombatable pure function
	virtual void ContinueAttack() override;
	virtual void EnableCombat() override;
	virtual void ResetAttack() override;
	virtual void DrawSheath() override;
	virtual void ResetDodge() override;
	virtual void ResetCombat() override;
	virtual void ResetTakeDamage() override;
	virtual void ResetMontage() override;

	// idamageable pure function
	virtual void TakeDamage(APawn* hitterPawn) override;
	virtual void SpawnEmitter(FHitResult result) override;
	virtual void StartHitStop(const float time) override;
	virtual void EndHitStop() override;

	// ipickupenable pure function
	virtual void PickUpItem(AItemBase* item) override;

protected:
	void InitAssets();														// 에셋 초기화
	void InitComponentsValue();												// 컴포넌트 값 초기화

	// 액션
	void MovementAction(const FInputActionValue& value);					// 이동
	void CancelMovementAction(const FInputActionValue& value);				// 이동 취소
	void CameraMovementAction(const FInputActionValue& value);				// 카메라 이동
	void JumpAction(const FInputActionValue& value);						// 점프
	void LightAttackAction(const FInputActionValue& value);					// 공격_약
	void HeavyAttackAction(const FInputActionValue& value);					// 공격_강
	void FocusAction(const FInputActionValue& value);						// 포커싱
	void CancelFocusAction(const FInputActionValue& value);					// 포커싱 취소
	void DrawSheathAction(const FInputActionValue& value);					// 무기 장비
	void InteractAction(const FInputActionValue& value);					// 상호작용
	void DodgeAction(const FInputActionValue& value);						// 회피
	void SprintAction(const FInputActionValue& value);						// 달리기
	void CancelSprintAction(const FInputActionValue& value);				// 달리기 취소

	void InventoryAction(const FInputActionValue& value);					// 인벤토리 on / off

private:
	void BindInputActions(class UInputComponent* PlayerInputComponent);		// 액션 바인딩
	void MappingContext() const;											// 맵핑

	void AdjustCameraRotation();											// 카메라 회전 조정
	void AdjustActorRotation();												// 캐릭터 회전 조정
	
	void TraceForInteractable();

	// 액션을 실행할 수 있는지 판단하기 위한 플래그 함수
	bool CanPerformMove();
	bool CanPerformAttack();
	bool CanPerformDodge();
	bool CanPerformTakeDamage();

	void TryMovement();
	void PerformMovement();

	void TryDrawSheath();
	void PerformDrawSheath();

	void TryAttack();
	void PerformAttack(int32 montageIndex, bool randomIndex, const ECharacterAction attackType);

	void TryDodge();
	void PerformDodge();
	void PerformRoll();
	
	void TrySprint();

	void TryInteract();
	void PerformInteract();

	void PerformAction(const ECharacterState state, const ECharacterAction action) const;

	float GetDegree(const FVector& vector) const;

#if ENABLE_DRAW_DEBUG
	// 디버깅용
	void DrawArrow() const;
#endif
};