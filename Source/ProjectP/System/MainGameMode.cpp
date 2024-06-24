// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "../Characters/Players/PlayerControls.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerControls>
		player(TEXT("/Script/CoreUObject.Class'/Script/ProjectP.PlayerControls'"));

	if (player.Succeeded())
		DefaultPawnClass = player.Class;
}