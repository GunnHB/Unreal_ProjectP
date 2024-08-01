// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * 
 */

class PROJECTP_API CBaseManager
{
public:
	CBaseManager();
	~CBaseManager();

private:
	static CBaseManager* mInstance;

public:
	bool Init() {return true;}
	
	static CBaseManager* GetInstance()
	{
		if(mInstance == nullptr)
			mInstance = new CBaseManager;

		return mInstance;
	}

	static void DestroyInstance()
	{
		if(mInstance != nullptr)
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}
};