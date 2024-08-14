// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"
#include "Components/ActorComponent.h"
#include "StateManageComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UStateManageComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	ECharacterState mCurrentState;

public:	
	// Sets default values for this component's properties
	UStateManageComponent();

	// getter
	ECharacterState GetCurrentState() const {return mCurrentState;}

	// setter
	void SetState(const ECharacterState newState);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void OnStateBegin(ECharacterState state);
	void OnStateEnd(ECharacterState state);
};
