// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "../../System/AIInfo.h"

#include "../../Component/RotateComponent.h"

#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UCLASS()
class PROJECTP_API AAIPawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UCapsuleComponent> mCapsule = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<USkeletalMeshComponent> mMesh = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<URotateComponent> mRotate = nullptr;

public:
	// Sets default values for this pawn's properties
	AAIPawn();

	// getter
	UCapsuleComponent* GetCapsuleComp() const {return mCapsule;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
