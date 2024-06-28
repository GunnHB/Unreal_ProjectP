// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "../Characters/Players/PlayerControls_SS.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerControls_SS>
		player(TEXT("/Script/CoreUObject.Class'/Script/ProjectP.PlayerControls_SS'"));

	if (player.Succeeded())
		DefaultPawnClass = player.Class;
}