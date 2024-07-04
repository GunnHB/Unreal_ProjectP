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
	TSubclassOf<class AAIPawn> mSpawnClass;		// 스폰할 폰의 클래스

	/*class AAIPawn* */TObjectPtr<class AAIPawn> mSpawnActor = nullptr;		// 스폰할 폰의 포인터

	UPROPERTY(EditAnywhere)
	float mSpawnTime = 0.f;				// 스폰시킬 시간

	float mCalculateSpawnTime = 0.f;	// 스폰용 계산 시간

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
