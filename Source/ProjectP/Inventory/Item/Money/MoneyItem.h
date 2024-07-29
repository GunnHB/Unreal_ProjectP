// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ItemBase.h"
#include "MoneyItem.generated.h"



UCLASS()
class PROJECTP_API AMoneyItem : public AItemBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle mMoney;
	
	FMoney* mMoneyData;

public:
	AMoneyItem();

protected:
	virtual void BeginPlay() override;
	virtual void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};