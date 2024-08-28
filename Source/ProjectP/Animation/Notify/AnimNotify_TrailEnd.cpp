// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_TrailEnd.h"

#include "../../Component/CombatComponent.h"
#include "../../Interface/CollisionEnable.h"

void UAnimNotify_TrailEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UCombatComponent* combatComp = MeshComp->GetOwner()->FindComponentByClass<UCombatComponent>();
	
	if(!IsValid(combatComp))
		return;

	if(!combatComp->IsMainWeaponNull())
	{
		ICollisionEnable* collisionEnable = Cast<ICollisionEnable>(combatComp->GetMainWeapon());

		if(collisionEnable != nullptr)
			collisionEnable->TrailEnd();
	}
}
