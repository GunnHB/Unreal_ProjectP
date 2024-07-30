// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponItem.h"

AWeaponItem::AWeaponItem()
{
	mCapsule->SetCollisionProfileName(TEXT("Weapon"));
}