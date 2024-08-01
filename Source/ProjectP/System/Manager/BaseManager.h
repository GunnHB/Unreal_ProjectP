// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

template <typename T>
class PROJECTP_API CBaseManager
{
protected:
	CBaseManager();
	~CBaseManager();
	
	static T* mInstance;

public:
	static T* GetInstance()
	{
		if(mInstance == nullptr)
			mInstance = new T;

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

	bool Init() {return true;}
};

template <typename T>
CBaseManager<T>::CBaseManager()
{
}

template <typename T>
CBaseManager<T>::~CBaseManager()
{
	
}

template <typename T>
T* CBaseManager<T>::mInstance = nullptr;