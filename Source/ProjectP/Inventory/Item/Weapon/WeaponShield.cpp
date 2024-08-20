// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponShield.h"

AWeaponShield::AWeaponShield()
{
	mCapsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
}

void AWeaponShield::SetData(FItem* itemData, bool relocate)
{
	Super::SetData(itemData, relocate);
}
