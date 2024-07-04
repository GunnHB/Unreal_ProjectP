// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

// ����� ��������Ʈ Ÿ�� ����
// DECLARE_DYNAMIC_DELEGATE���� �ϸ� ����ȭ�Ǿ� �������Ʈ������ ��밡��
// DECLARE_DELEGATE���� �ϸ� �ϳ��� �̺�Ʈ�� ��� ����
// DECLARE_MULTICAST_DELEGATE���� �ϸ� ���� ���� �̺�Ʈ ��� ����
// �Ķ���Ͱ� �ʿ��ϸ� �߰��� �� ����
DECLARE_MULTICAST_DELEGATE(FAIDeathDelegate);

UCLASS()
class PROJECTP_API AAIPawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> mCapsule = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> mSkeletalMesh = nullptr;

	FAIDeathDelegate mDeathDelegate;

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;	// ���� ���ŵ� �� ȣ��

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;	// �ǰ�

protected:
	virtual void InitAssets();
	virtual void InitComponentsValue();

public:
	TObjectPtr<UCapsuleComponent> GetCapsuleComponent() const { return mCapsule; }

public:
	// � Ŭ������ ��� �Լ��� ��ϵ��� �𸣱� ������ template ���
	template<typename T>
	void AddDeathDelegate(T* object, void (T::* Func)())
	{
		// ��������Ʈ�� �Լ��� ���
		mDeathDelegate.AddUObject(object, Func);
	}
};
