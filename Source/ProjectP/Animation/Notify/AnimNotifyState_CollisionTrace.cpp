// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_CollisionTrace.h"

#include "../..//Component/CombatComponent.h"
#include "ProjectP/Component/CollisionComponent.h"

void UAnimNotifyState_CollisionTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(!IsValid(MeshComp))
		return;

	if(mCollision == nullptr)
		SetCollision(MeshComp->GetOwner());

	mCollision->CollisionEnable();
}

void UAnimNotifyState_CollisionTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(!IsValid(MeshComp))
		return;

	if(mCollision == nullptr)
		SetCollision(MeshComp->GetOwner());
}

void UAnimNotifyState_CollisionTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(!IsValid(MeshComp))
		return;

	if(mCollision == nullptr)
		SetCollision(MeshComp->GetOwner());

	mCollision->CollisionDisable();
}

void UAnimNotifyState_CollisionTrace::SetCollision(AActor* actor)
{
	UCombatComponent* combat = actor->GetComponentByClass<UCombatComponent>();

	if(!IsValid(combat) || combat->GetMainWeapon() == nullptr)
		return;

	mCollision = combat->GetOwner()->GetComponentByClass<UCollisionComponent>();
}
