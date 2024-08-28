// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Interface/Combatable.h"
#include "../../Interface/Damageable.h"

#include "../AI/AIPawn.h"
#include "EnemyPawn.generated.h"

UCLASS()
class PROJECTP_API AEnemyPawn : public AAIPawn, public ICombatable, public IDamageable, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UEnemyMovementComponent> mMovement = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UCombatComponent> mCombat = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<class UFocusComponent> mFocus = nullptr;
	
	UPROPERTY(EditAnywhere) TArray<class AAIPatrolPoint*> mPatrolPointArray;
	
	TObjectPtr<class UEnemyAnimInstance> mAnimInstance = nullptr;
	TObjectPtr<UParticleSystem> mDamageParticle = nullptr;
	
	FEnemy mEnemyData;
	uint8 mTeamID = 10;
	
	TObjectPtr<class UEnemyStat> mEnemyStat = nullptr;

	FTimerHandle mHitStopTimeHandle;

	// ICombatable pure function
	virtual void ContinueAttack() override;
	virtual void DrawSheath() override;
	virtual void EnableCombat() override;
	virtual void ResetAttack() override;
	virtual void ResetCombat() override;
	virtual void ResetDodge() override;
	virtual void ResetTakeDamage() override;
	virtual void ResetMontage() override;

	// IDamageable pure function
	virtual void TakeDamage(APawn* hitterPawn) override;
	virtual void SpawnEmitter(FHitResult result) override;
	virtual void StartHitStop(const float time) override;
	virtual void EndHitStop() override;

public:
	AEnemyPawn();

	// getter
	TArray<AAIPatrolPoint*> GetPatrolPointArray() const {return mPatrolPointArray;}
	UCombatComponent* GetCombatComp() const {return mCombat;}
	UEnemyAnimInstance* GetAnimInstance() const {return mAnimInstance;}
	uint8 GetTeamID() const {return mTeamID;}
	
	// setter
	void SetTeamID(const uint8 value) {mTeamID = value;}

	// 지금은 사용하지 않아서 우선 주석 처리
	// void TryDrawSheath(const bool isEquipped) const;

	// for guard
	void PerformGuard() const;
	void ReleaseGuard() const;

	// for focus
	void SetAimOffsetDegree(const float value) const;
	void SetMovementDegree(const float value) const;

	bool IsDead() const;

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

	void InitWeapon();

	void SetTakeDamage(const APawn* hitter);
};
