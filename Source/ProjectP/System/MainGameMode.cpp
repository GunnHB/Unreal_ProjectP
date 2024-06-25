// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "../Characters/Players/PlayerControls_Crunch.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerControls_Crunch>
		player(TEXT("/Script/CoreUObject.Class'/Script/ProjectP.PlayerControls_Crunch'"));

	if (player.Succeeded())
		DefaultPawnClass = player.Class;
}