// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ResetTakeDamage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UAnimNotify_ResetTakeDamage : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
