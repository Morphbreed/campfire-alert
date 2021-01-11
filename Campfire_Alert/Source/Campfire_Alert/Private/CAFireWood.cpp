// Fill out your copyright notice in the Description page of Project Settings.


#include "CAFireWood.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "TimerManager.h"

// Sets default values
ACAFireWood::ACAFireWood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	MeshComp->SetupAttachment(RootComponent);
	BoxComp->SetupAttachment(SceneComp);

	RotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComp"));
	TicksProcessed = 0;

	TimeToRespawnMin = 3;
	TimeToRespawnMax = 10;

	TimeToRespawn = FMath::RandRange(TimeToRespawnMin, TimeToRespawnMax);

}

// Called when the game starts or when spawned
void ACAFireWood::BeginPlay()
{
	Super::BeginPlay();
}

void ACAFireWood::OnPickUp()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	RespawnSpawnWood();
}

void ACAFireWood::RespawnTick()
{
	TicksProcessed++;

	if (TicksProcessed >= TimeToRespawn)
	{
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
}

void ACAFireWood::RespawnSpawnWood()
{
	TicksProcessed = 0;
	TimeToRespawn = FMath::RandRange(TimeToRespawnMin, TimeToRespawnMax);
	UE_LOG(LogTemp, Warning, TEXT("Time to respawn: %d"), TimeToRespawn);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTick, this, &ACAFireWood::RespawnTick, 1.f, true);
}

// Called every frame
void ACAFireWood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

