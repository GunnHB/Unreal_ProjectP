// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../System/GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

// 사용자 델리게이트 타입 선언
// DECLARE_DYNAMIC_DELEGATE으로 하면 직렬화되어 블루프린트에서도 사용가능
// DECLARE_DELEGATE으로 하면 하나의 이벤트만 등록 가능
// DECLARE_MULTICAST_DELEGATE으로 하면 여러 개의 이벤트 등록 가능
// 파라미터가 필요하면 추가할 수 있음
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;	// 폰이 제거될 때 호출

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;	// 피격

protected:
	virtual void InitAssets();
	virtual void InitComponentsValue();

public:
	TObjectPtr<UCapsuleComponent> GetCapsuleComponent() const { return mCapsule; }

public:
	// 어떤 클래스의 멤버 함수가 등록될지 모르기 때문에 template 사용
	template<typename T>
	void AddDeathDelegate(T* object, void (T::* Func)())
	{
		// 델리게이트에 함수를 등록
		mDeathDelegate.AddUObject(object, Func);
	}
};
