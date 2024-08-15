// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_CollisionTrace.h"

#include "../../Component/CombatComponent.h"
#include "../../Component/CollisionComponent.h"

void UAnimNotifyState_CollisionTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(!IsValid(MeshComp))
		return;
	
	UCombatComponent* combatComp = MeshComp->GetOwner()->FindComponentByClass<UCombatComponent>();
	
	if(!IsValid(combatComp))
		return;
	
	UCollisionComponent* collisionComp = combatComp->GetMainCollisionComp();
	
	if(IsValid(collisionComp))
		collisionComp->CollisionEnable();
}

void UAnimNotifyState_CollisionTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(!IsValid(MeshComp))
		return;
	
	UCombatComponent* combatComp = MeshComp->GetOwner()->FindComponentByClass<UCombatComponent>();
	
	if(!IsValid(combatComp))
		return;
	
	UCollisionComponent* collisionComp = combatComp->GetMainCollisionComp();
	
	if(IsValid(collisionComp))
		collisionComp->CollisionTrace();
}

void UAnimNotifyState_CollisionTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(!IsValid(MeshComp))
		return;
	
	UCombatComponent* combatComp = MeshComp->GetOwner()->FindComponentByClass<UCombatComponent>();
	
	if(!IsValid(combatComp))
		return;
	
	UCollisionComponent* collisionComp = combatComp->GetMainCollisionComp();
	
	if(IsValid(collisionComp))
		collisionComp->CollisionDisable();
}