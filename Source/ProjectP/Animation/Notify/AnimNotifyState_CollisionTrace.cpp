// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_CollisionTrace.h"

#include "../..//Component/CombatComponent.h"
#include "ProjectP/Component/CollisionComponent.h"
#include "ProjectP/Inventory/Item/Weapon/WeaponBase.h"

void UAnimNotifyState_CollisionTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if(!IsValid(MeshComp))
		return;

	if(!IsValid(mCollision))
		SetCollision(MeshComp->GetOwner());

	if(IsValid(mCollision))
		mCollision->CollisionEnable();
}

void UAnimNotifyState_CollisionTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(IsValid(mCollision))
		mCollision->CollisionTrace();
}

void UAnimNotifyState_CollisionTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(IsValid(mCollision))
		mCollision->CollisionDisable();
}

void UAnimNotifyState_CollisionTrace::SetCollision(AActor* actor)
{
	UCombatComponent* combat = actor->GetComponentByClass<UCombatComponent>();

	if(!IsValid(combat) || combat->IsMainWeaponNull())
		return;

	UCollisionComponent* component = combat->GetMainWeapon()->GetComponentByClass<UCollisionComponent>();
	
	if(IsValid(component))
		mCollision = component;
}
