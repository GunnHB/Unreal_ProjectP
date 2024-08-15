#pragma once

#include "EngineMinimal.h"
#include "Engine.h"

#include "GameInfo.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ProjectP, Warning, All);

class GameValue
{
private:
	static int32 MaxMoney;

	static float MaxWalkSpeed;
	static float MaxJogSpeed;
	static float KnockBackAmount;

	static float MoveToTargetLimitAmount;
	
	static FName CollisionStartSocketFName;
	static FName CollisionEndSocketFName;
	static FName PelvisSocketFName;

	static FName PlayerFName;
	static FName EnemyFName;
	static FName ItemFName;

	static FName PatrolIndexFName;
	static FName TargetLocationFName;

	static FString BTTaskMoveToTargetFName;

public:
	static int32 GetMaxMoney() { return MaxMoney; }

	static float GetMaxWalkSpeed() {return MaxWalkSpeed;}
	static float GetMaxJogSpeed() {return MaxJogSpeed;}
	static float GetKnockBackAmount() {return KnockBackAmount;}
	
	static float GetMoveToTargetLimitAmount() {return MoveToTargetLimitAmount;}
	
	static FName GetCollisionStartSocketName() {return CollisionStartSocketFName;}
	static FName GetCollisionEndSocketName() {return CollisionEndSocketFName;}
	static FName GetPelvisSocketName() {return PelvisSocketFName;}

	static FName GetPlayerFName() {return PlayerFName;}
	static FName GetEnemyFName() {return EnemyFName;}
	static FName GetItemFName() {return ItemFName;}

	static FName GetPatrolIndexFName() {return PatrolIndexFName;}
	static FName GetTargetLocationFName() {return TargetLocationFName;}

	static FString GetBTTaskMoveToTargetFName() {return BTTaskMoveToTargetFName;}
};

enum ECharacterState : int8
{
	None = -1,
	Idle,
	Movement,
	Attack,
	Dodge,
	Focus,
};

UENUM()
enum class EMoneyType : int8
{
	None = -1,
	Green,
	Blue,
	Red,
	Silver,
	Gold,
};

UENUM()
enum class EItemType : int8
{
	None = -1,
	Weapon,
	Armor,
	Consumption,
	Material,
	Money,
};

UENUM()
enum class EWeaponType : int8
{
	None = -1,
	Sword,
	Shield,
};

UENUM()
enum class ESwordType : int8
{
	None = -1,
	OneHand,
	TwoHand,
};

USTRUCT(BlueprintType)
struct FMoney : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EMoneyType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) uint8 amount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UStaticMesh* mesh;
};

USTRUCT()
struct FItem : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EItemType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TSubclassOf<class AItemBase> item_class;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UStaticMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString item_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString item_desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float capsule_half_height;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float capsule_radius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FTransform mesh_transform;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName ref_row_name;
};

USTRUCT()
struct FWeapon : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EWeaponType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) uint8 ability_value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) uint8 duration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName sheath_socket_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName hand_socket_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName ref_row_name;
};

USTRUCT()
struct FSword : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) ESwordType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UAnimMontage* montage_draw;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UAnimMontage* montage_sheath;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<UAnimMontage*> montage_attack_array;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UAnimMontage* montage_dodge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UAnimMontage* montage_roll;
};

USTRUCT()
struct FEnemy : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<USkeletalMesh> mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString enemy_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString enemy_desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float capsule_half_height;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float capsule_radius;
};
