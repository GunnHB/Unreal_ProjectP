// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Interface/Combatable.h"
#include "../../Interface/Damageable.h"

#include "../AI/AIPawn.h"
#include "EnemyPawn.generated.h"

UCLASS()
class PROJECTP_API AEnemyPawn : public AAIPawn, public ICombatable, public IDamageable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UEnemyMovementComponent> mMovement = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UCombatComponent> mCombat = nullptr;
	UPROPERTY(EditAnywhere) TArray<class AAIPatrolPoint*> mPatrolPointArray;

	TObjectPtr<class UEnemyAnimInstance> mAnimInstance = nullptr;
	
	FEnemy mEnemyData;

	// ICombatable pure function
	virtual void ContinueAttack() override;
	virtual void DrawSheath() override;
	virtual void EnableCombat() override;
	virtual void ResetAttack() override;
	virtual void ResetCombat() override;
	virtual void ResetDodge() override;
	virtual void ResetTakeDamage() override;

	// IDamageable pure function
	virtual void TakeDamage(APawn* hitterPawn) override;
	virtual void StartHitStop(const float time) override;
	virtual void EndHitStop() override;

public:
	AEnemyPawn();

	// getter
	TArray<AAIPatrolPoint*> GetPatrolPointArray() const {return mPatrolPointArray;}
	

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PossessedBy(AController* NewController) override;
};
