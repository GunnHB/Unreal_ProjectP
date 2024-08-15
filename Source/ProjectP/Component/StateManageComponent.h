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
	ECharacterState mCurrentCharacterState;
	ECharacterAction mCurrentCharacterAction;

public:	
	// Sets default values for this component's properties
	UStateManageComponent();

	// getter
	ECharacterState GetCurrentState() const {return mCurrentCharacterState;}

	void SetState(const ECharacterState newState);
	void ResetState();
	bool IsCurrentStateEqual(const ECharacterState state) const;
	bool IsCurrentStateNotEqualToAny(TArray<int8> stateArray) const;

	void SetAction(const ECharacterAction newAction);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void OnStateBegin(ECharacterState state);
	void OnStateEnd(ECharacterState state);

	void OnActionBegin(ECharacterAction action);
	void OnActionEnd(ECharacterAction action);

	void PrintCurrentState();
};
