// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Potion.h"

#include "../../Interface/Recoverable.h"

void UAnimNotify_Potion::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(!IsValid(MeshComp))
		return;
	
	IRecoverable* recoverable = Cast<IRecoverable>(MeshComp->GetOwner());

	if(recoverable != nullptr)
		recoverable->Recovery();
}
