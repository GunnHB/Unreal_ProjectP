// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AIPatrolPoint.generated.h"

UCLASS()
class PROJECTP_API AAIPatrolPoint : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<USceneComponent> mRoot = nullptr;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UArrowComponent> mArrow = nullptr;
#endif

public:	
	// Sets default values for this actor's properties
	AAIPatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
