// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "../Characters/Player/PlayerControls.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerControls>
		asset(TEXT("/Script/CoreUObject.Class'/Script/ProjectP.PlayerControls'"));

	if (asset.Succeeded())
		DefaultPawnClass = asset.Class;
}