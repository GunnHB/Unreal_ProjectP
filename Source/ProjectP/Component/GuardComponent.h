// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../System/GameInfo.h"

#include "Components/ActorComponent.h"
#include "GuardComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UGuardComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGuardComponent();
};
