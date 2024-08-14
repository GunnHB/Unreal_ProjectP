
#include "GameInfo.h"

DEFINE_LOG_CATEGORY(ProjectP);

int32 GameValue::MaxMoney = 9999;

float GameValue::MaxWalkSpeed = 100.f;
float GameValue::MaxJogSpeed = 400.f;
float GameValue::KnockBackAmount = 85.f;

FName GameValue::CollisionStartSocketFName = "CollisionStart";
FName GameValue::CollisionEndSocketFName = "CollisionEnd";
FName GameValue::PelvisSocketFName = "pelvis";

FName GameValue::PlayerFName = "Player";
FName GameValue::EnemyFName = "Enemy";
FName GameValue::ItemFName = "Item";

FName GameValue::PatrolIndexFName = "PatrolIndex";
FName GameValue::TargetLocationFName = "TargetLocation";

FString GameValue::BTTaskMoveToTargetFName = "MoveToTarget";