#pragma once

#include "EngineMinimal.h"
#include "Engine.h"

#include "GameInfo.generated.h"

class GameValue
{
private:
	static int32 MaxMoney;

public:
	static int32 GetMaxMoney() { return MaxMoney; }
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
struct FWeapon : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) EWeaponType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) UStaticMesh* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) uint8 ability_value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) uint8 duration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName sheath_socket_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FName hand_socket_name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 red_id;
};

USTRUCT()
struct FSword : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 id;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) ESwordType type;
};
