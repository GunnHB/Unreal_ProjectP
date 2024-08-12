// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_CollisionTrace.h"

#include "../../Interface/Combatable.h"
#include "../../Interface/CollisionEnable.h"
#include "../../Component/CollisionComponent.h"
#include "../../Component/CombatComponent.h"
#include "../../Inventory/Item/Weapon/WeaponSword.h"

void UAnimNotifyState_CollisionTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(!IsValid(MeshComp))
		return;

	ICombatable* combatable = Cast<ICombatable>(MeshComp->GetOwner());

	if(combatable != nullptr)
	{
		ICollisionEnable* collisionEnable = Cast<ICollisionEnable>(combatable->GetCombatComponent()->GetMainWeapon());
		
		if(collisionEnable != nullptr)
			collisionEnable->GetCollision()->CollisionEnable();
	}
}

void UAnimNotifyState_CollisionTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ICombatable* combatable = Cast<ICombatable>(MeshComp->GetOwner());

	if(combatable != nullptr)
	{
		ICollisionEnable* collisionEnable = Cast<ICollisionEnable>(combatable->GetCombatComponent()->GetMainWeapon());
		
		if(collisionEnable != nullptr)
			collisionEnable->GetCollision()->CollisionTrace();
	}
}

void UAnimNotifyState_CollisionTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ICombatable* combatable = Cast<ICombatable>(MeshComp->GetOwner());

	if(combatable != nullptr)
	{
		ICollisionEnable* collisionEnable = Cast<ICollisionEnable>(combatable->GetCombatComponent()->GetMainWeapon());
		
		if(collisionEnable != nullptr)
			collisionEnable->GetCollision()->CollisionDisable();
	}
}
