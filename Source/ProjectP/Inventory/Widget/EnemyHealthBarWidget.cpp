// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHealthBarWidget.h"

void UEnemyHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mEnemyNameTextBlock = Cast<UTextBlock>(GetWidgetFromName(GameValue::GetUIEnemyNameTextBlockFName()));
	mEnemyHPBar = Cast<UProgressBar>(GetWidgetFromName(GameValue::GetUIEnemyHPBarFName()));
}

void UEnemyHealthBarWidget::InitEnemyStat()
{
}