// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHealthBarWidget.h"

#include "../../Data/EnemyStat.h"

void UEnemyHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mEnemyNameTextBlock = Cast<UTextBlock>(GetWidgetFromName(GameValue::GetUIEnemyNameTextBlockFName()));
	mEnemyHPBar = Cast<UProgressBar>(GetWidgetFromName(GameValue::GetUIEnemyHPBarFName()));
}

void UEnemyHealthBarWidget::InitEnemyHP(const UEnemyStat* enemyStat)
{
	mEnemyHPBar->SetPercent(enemyStat->GetCurrCharacterHP() / enemyStat->GetMaxCharacterHP());
}