// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../System/GameInfo.h"
#include "GameFramework/Actor.h"
#include "EquipmentBase.generated.h"

UCLASS()
class PROJECTP_API AEquipmentBase : public AActor
{
	GENERATED_BODY()

// protected:
	// TObjectPtr<UStaticMeshComponent> 
	
public:	
	// Sets default values for this actor's properties
	AEquipmentBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
