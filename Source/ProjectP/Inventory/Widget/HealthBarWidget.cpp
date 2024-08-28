// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "HeartWidget.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	mHealthBarWrapBox = Cast<UWrapBox>(GetWidgetFromName(GameValue::GetUIHealthBarWrapBoxFName()));
}