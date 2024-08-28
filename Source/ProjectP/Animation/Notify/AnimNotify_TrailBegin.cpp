// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_TrailBegin.h"

#include "../../Component/CombatComponent.h"
#include "../../Interface/CollisionEnable.h"

void UAnimNotify_TrailBegin::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	UCombatComponent* combatComp = MeshComp->GetOwner()->FindComponentByClass<UCombatComponent>();
	
	if(!IsValid(combatComp))
		return;

	if(!combatComp->IsMainWeaponNull())
	{
		ICollisionEnable* collisionEnable = Cast<ICollisionEnable>(combatComp->GetMainWeapon());

		if(collisionEnable != nullptr)
			collisionEnable->TrailBegin();
	}
}