// Fill out your copyright notice in the Description page of Project Settings.


#include "OneHandSword.h"

AOneHandSword::AOneHandSword()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		meshAsset(TEXT("/Script/Engine.StaticMesh'/Game/EssentialAnimation/SwordShield/Demo/Mannequin/Weapon/SM_Sword.SM_Sword'"));

	if(meshAsset.Succeeded())
		mStaticMesh->SetStaticMesh(meshAsset.Object);

	mAttachSocketName = "SwordHipAttachSocket";
}
