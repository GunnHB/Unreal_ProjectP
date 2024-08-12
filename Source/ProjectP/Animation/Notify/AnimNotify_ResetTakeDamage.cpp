// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ResetTakeDamage.h"

#include "../../Interface/Combatable.h"
#include "../../Component/CombatComponent.h"
#include "../../Interface/CollisionEnable.h"

void UAnimNotify_ResetTakeDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(!IsValid(MeshComp))
		return;

	ICombatable* combatable = Cast<ICombatable>(MeshComp->GetOwner());

	if(combatable != nullptr)
		combatable->ResetTakeDamage();
}
