// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControls.h"
#include "PlayerControls_Crunch.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API APlayerControls_Crunch : public APlayerControls
{
	GENERATED_BODY()
	
public:
	APlayerControls_Crunch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void InitAssets();
	void InitCompoValues();
};
