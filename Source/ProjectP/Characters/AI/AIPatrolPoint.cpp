// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrolPoint.h"

#include "Components/ArrowComponent.h"

// Sets default values
AAIPatrolPoint::AAIPatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

#if WITH_EDITORONLY_DATA
	mArrow = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	mArrow->ArrowColor = FColor(150, 200, 255);
	mArrow->bTreatAsASprite = true;
	mArrow->SetupAttachment(mRoot);
	mArrow->bIsScreenSizeScaled = true;
	mArrow->SetSimulatePhysics(false);
#endif

#if ENABLE_DRAW_DEBUG
	mRoot->bVisualizeComponent = true;
#endif
}

// Called when the game starts or when spawned
void AAIPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

