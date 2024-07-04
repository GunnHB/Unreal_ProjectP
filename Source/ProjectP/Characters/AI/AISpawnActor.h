// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"

#include "../../System/GameInfo.h"
#include "GameFramework/Actor.h"
#include "AISpawnActor.generated.h"

UCLASS()
class PROJECTP_API AAISpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawnActor();

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* mRoot;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* mArrow;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAIPawn> mSpawnClass;		// ������ ���� Ŭ����

	/*class AAIPawn* */TObjectPtr<class AAIPawn> mSpawnActor = nullptr;		// ������ ���� ������

	UPROPERTY(EditAnywhere)
	float mSpawnTime = 0.f;				// ������ų �ð�

	float mCalculateSpawnTime = 0.f;	// ������ ��� �ð�

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Spawn();

	UFUNCTION()
	void AIDeathDelegate();
};
