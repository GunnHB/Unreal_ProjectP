
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

float GameValue::EnemySightRadius = 2000.f;
float GameValue::EnemyLoseSightRadius = 2500.f;
float GameValue::EnemyVisionAngleDegree = 100.f;

float GameValue::EnemyReadyToCombatPatrolDistance = 800.f;
float GameValue::EnemyCombatPatrolDistance = 300.f;

float GameValue::EnableToFocusRange = 1500.f;
float GameValue::EnableToFocusRadius = 500.f;

FName GameValue::CollisionStartSocketFName = "CollisionStart";
FName GameValue::CollisionEndSocketFName = "CollisionEnd";
FName GameValue::PelvisSocketFName = "pelvis";

FName GameValue::PlayerFName = "Player";
FName GameValue::EnemyFName = "Enemy";
FName GameValue::ItemFName = "Item";

FName GameValue::PatrolIndexFName = "PatrolIndex";
FName GameValue::TargetLocationFName = "TargetLocation";
FName GameValue::TargetFName = "Target";
FName GameValue::EnableToCombatFName = "EnableToCombat";
FName GameValue::KeepEnemyInCheckFName = "KeepEnemyInCheck";
FName GameValue::WasDrawFName = "WasDraw";
FName GameValue::AttackableFName = "Attackable";
FName GameValue::CombatPatrolLocationFName = "CombatPatrolLocation";

FString GameValue::BTTaskMoveToTargetFString = "MoveToTarget";
FString GameValue::BTTaskWaitToKeepEnemyInCheckFString = "WaitToKeepEnemyInCheck";