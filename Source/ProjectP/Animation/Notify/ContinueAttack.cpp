// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinueAttack.h"

void UContinueAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(!IsValid(MeshComp))
		return;

	
}
