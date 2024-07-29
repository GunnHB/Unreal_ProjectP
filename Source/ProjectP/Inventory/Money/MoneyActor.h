// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "../../System/GameInfo.h"
#include "GameFramework/Actor.h"
#include "MoneyActor.generated.h"

UCLASS()
class PROJECTP_API AMoneyActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> mCapsule;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> mMesh;
	UPROPERTY(EditAnywhere)
	MoneyType mMoneyType;

	TObjectPtr<UDataTable> mMoneyTable;
	FMoney* mData;
	
public:	
	// Sets default values for this actor's properties
	AMoneyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStaticMesh(const MoneyType& moneyType);

private:
	UFUNCTION()
	void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FName GetRowNameByMoneyType();
};