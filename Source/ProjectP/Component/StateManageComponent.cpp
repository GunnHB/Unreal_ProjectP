// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManageComponent.h"

// Sets default values for this component's properties
UStateManageComponent::UStateManageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UStateManageComponent::SetState(const ECharacterState newState)
{
	// 같은 상태에서는 굳이 전환할 필요X
	if(mCurrentCharacterState == newState)
		return;
	
	OnStateEnd(mCurrentCharacterState);
	
	mCurrentCharacterState = newState;
	OnStateBegin(mCurrentCharacterState);
}

bool UStateManageComponent::IsCurrentStateEqual(const ECharacterState state) const
{
	return state == mCurrentCharacterState;
}

bool UStateManageComponent::IsCurrentValueNotEqualToAny(TArray<int8> stateArray) const
{
	for(const int8 state : stateArray)
	{
		if(state ==  static_cast<int8>(mCurrentCharacterState))
			return false;
	}

	return true;
}

void UStateManageComponent::SetAction(const ECharacterAction newAction)
{
	if(mCurrentCharacterAction != newAction)
		return;

	OnActionEnd(mCurrentCharacterAction);

	mCurrentCharacterAction = newAction;
	OnActionBegin(mCurrentCharacterAction);
}

bool UStateManageComponent::IsCurrentStateEqual(const ECharacterAction action) const
{
	return action == mCurrentCharacterAction;
}

// Called when the game starts
void UStateManageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UStateManageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...

	PrintCurrentState();
}

void UStateManageComponent::OnStateBegin(ECharacterState state)
{
}

void UStateManageComponent::OnStateEnd(ECharacterState state)
{
}

void UStateManageComponent::OnActionBegin(ECharacterAction action)
{
}

void UStateManageComponent::OnActionEnd(ECharacterAction action)
{
}

void UStateManageComponent::PrintCurrentState()
{
	FString state;

	switch (mCurrentCharacterState)
	{
	case ECharacterState::General:
		state = "General";
		break;
	case ECharacterState::Attack:
		state = "Attack";
		break;
	case ECharacterState::Dodge:
		state = "Dodge";
		break;
	case ECharacterState::Dead:
		state = "Dead";
		break;
	}

	UE_LOG(ProjectP, Warning, TEXT("current state is %s"), *state);
}
