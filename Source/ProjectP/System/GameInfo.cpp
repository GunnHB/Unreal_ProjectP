
#include "GameInfo.h"

DEFINE_LOG_CATEGORY(ProjectP);

int32 GameValue::MaxMoney = 9999;

float GameValue::WalkSpeed = 100.f;
float GameValue::JogSpeed = 400.f;
float GameValue::SprintSpeed = 800.f;
float GameValue::KnockBackAmount = 85.f;

float GameValue::MoveToTargetLimitAmount = 50.f;

FName GameValue::CollisionStartSocketFName = "CollisionStart";
FName GameValue::CollisionEndSocketFName = "CollisionEnd";
FName GameValue::PelvisSocketFName = "pelvis";

FName GameValue::PlayerFName = "Player";
FName GameValue::EnemyFName = "Enemy";
FName GameValue::ItemFName = "Item";

FName GameValue::PatrolIndexFName = "PatrolIndex";
FName GameValue::TargetLocationFName = "TargetLocation";

FString GameValue::BTTaskMoveToTargetFName = "MoveToTarget";