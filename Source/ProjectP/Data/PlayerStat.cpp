// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStat.h"

#include "../Characters/Player/InGamePlayerController.h"

void UPlayerStat::InitStat(const APawn* owner)
{
	Super::InitStat(owner);

	if(IsValid(owner))
	{
		AInGamePlayerController* controller = owner->GetController<AInGamePlayerController>();

		if(IsValid(controller))
		{
			controller->SetPlayerStamina(mCurrCharacterStamina);
		}
	}
}
