// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ResetMontage.h"

#include "../../Interface/Combatable.h"

void UAnimNotify_ResetMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(!IsValid(MeshComp))
		return;

	ICombatable* combatable = Cast<ICombatable>(MeshComp->GetOwner());

	if(combatable != nullptr)
		combatable->ResetMontage();
}
