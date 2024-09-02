// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseManager.h"

/**
 * 
 */
class PROJECTP_API CUIManager : public CBaseManager<CUIManager>
{
public:
	CUIManager();
	~CUIManager();

	void InitWorld(UWorld* world);

protected:
	TObjectPtr<UWorld> mWorld = nullptr;
	
	TSubclassOf<class UMainWidget> mMainWidgetClass = nullptr;
	TObjectPtr<UMainWidget> mMainWidget = nullptr;

public:
	UMainWidget* GetMainWidget();
};
