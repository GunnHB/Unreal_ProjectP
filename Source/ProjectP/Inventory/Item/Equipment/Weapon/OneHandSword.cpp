// Fill out your copyright notice in the Description page of Project Settings.


#include "OneHandSword.h"

AOneHandSword::AOneHandSword()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		meshAsset(TEXT("/Script/Engine.StaticMesh'/Game/04_Inventory/Model/03_Sword/Knight_s_Broadsword/3DModel/SM_Knights_Broadsword.SM_Knights_Broadsword'"));

	if(meshAsset.Succeeded())
		mStaticMesh->SetStaticMesh(meshAsset.Object);

	mAttachSocketName = "SwordHipAttachSocket";
}
