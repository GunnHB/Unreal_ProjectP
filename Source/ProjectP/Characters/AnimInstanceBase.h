// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

protected:
	TObjectPtr<APawn> mPawn = nullptr;
	TObjectPtr<UPawnMovementComponent> mPawnMovement = nullptr;

	// getter
	APawn* GetThisPawn() const {return mPawn;}
	UPawnMovementComponent* GetThisPawnMovement() const {return mPawnMovement;}

	// base variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float mSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float mDegree = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float mTakeDamageDegree = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bTakeDamage = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) bool bIsGuarding = false;

	// override by UAnimInstance
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	bool GetIsGuardingFlag() const {return bIsGuarding;}
	
	void SetTakeDamageDegree(const float value) {mTakeDamageDegree = value;}
	void SetTakeDamageFlag(const bool value) {bTakeDamage = value;}
	void SetIsGuardingFlag(const bool value) {bIsGuarding = value;}
};
