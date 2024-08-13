
#include "GameInfo.h"

DEFINE_LOG_CATEGORY(ProjectP);

int32 GameValue::MaxMoney = 9999;

float GameValue::MaxWalkSpeed = 400.f;
float GameValue::KnockBackAmount = 85.f;

FName GameValue::CollisionStartSocketName = "CollisionStart";
FName GameValue::CollisionEndSocketName = "CollisionEnd";
FName GameValue::PelvisSocketName = "pelvis";