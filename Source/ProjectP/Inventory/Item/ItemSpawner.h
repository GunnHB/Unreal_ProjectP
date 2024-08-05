// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class PROJECTP_API AItemSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<USceneComponent> mRoot = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UArrowComponent> mArrow = nullptr;

	UPROPERTY(EditAnywhere) FDataTableRowHandle mTableHandle;
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnItem() const;
};
