// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStat.h"

#include "../Characters/AI/EnemyController.h"

void UEnemyStat::InitStat(const APawn* owner)
{
	Super::InitStat(owner);

	if(IsValid(owner))
	{
		AEnemyController* controller = owner->GetController<AEnemyController>();

		if(IsValid(controller))
			controller->SetEnemyHP(50.f);
	}
}
