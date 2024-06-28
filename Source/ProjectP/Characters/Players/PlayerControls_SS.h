// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerControls.h"
#include "PlayerControls_SS.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APlayerControls_SS : public APlayerControls
{
	GENERATED_BODY()

private:
	TObjectPtr<class UPlayerAnimInstance_SS> mAnimInstance = nullptr;
	
public:
	APlayerControls_SS();

#pragma region Base
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

#pragma region Initialize
protected:
	virtual void InitAssets() override;
	virtual void InitComponentValues() override;
#pragma endregion
};
