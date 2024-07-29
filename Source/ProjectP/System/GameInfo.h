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
enum class MoneyType : uint8
{
	Green,
	Blue,
	Red,
	Silver,
	Gold,
};

USTRUCT(BlueprintType)
struct FMoney : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	MoneyType Type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Mesh;
};