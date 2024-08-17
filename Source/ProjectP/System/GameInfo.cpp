
#include "GameInfo.h"

DEFINE_LOG_CATEGORY(ProjectP);

int32 GameValue::MaxMoney = 9999;

float GameValue::WalkSpeed = 100.f;
float GameValue::JogSpeed = 400.f;
float GameValue::ChaseSpeed = 500.f;
float GameValue::SprintSpeed = 800.f;
float GameValue::KnockBackAmount = 85.f;

float GameValue::MoveToTargetLimitAmount = 50.f;
float GameValue::EnoughToCombatDistance = 250.f;
float GameValue::KeepEnemyInCheckTime = 8.f;

float GameValue::EnemySightRadius = 3000.f;
float GameValue::EnemyLoseSightRadius = 3500.f;
float GameValue::EnemyVisionAngleDegree = 65.f;

FName GameValue::CollisionStartSocketFName = "CollisionStart";
FName GameValue::CollisionEndSocketFName = "CollisionEnd";
FName GameValue::PelvisSocketFName = "pelvis";

FName GameValue::PlayerFName = "Player";
FName GameValue::EnemyFName = "Enemy";
FName GameValue::ItemFName = "Item";

FName GameValue::PatrolIndexFName = "PatrolIndex";
FName GameValue::TargetLocationFName = "TargetLocation";
FName GameValue::TargetFName = "Target";
FName GameValue::KeepEnemyInCheckFName = "KeepEnemyInCheck";
FName GameValue::DrawSheathFName = "DrawSheath";

FString GameValue::BTTaskMoveToTargetFString = "MoveToTarget";
FString GameValue::BTTaskWaitToKeepEnemyInCheckFString = "WaitToKeepEnemyInCheck";