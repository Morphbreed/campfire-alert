// Fill out your copyright notice in the Description page of Project Settings.


#include "CACampfire.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "CACampfire.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"



// Sets default values
ACACampfire::ACACampfire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorScale = 1.f;
	FireTickInterval = 1.f;
	ShrinkValue = .1f;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(RootComponent);

	
	CampFireFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));
	CampFireFire->SetupAttachment(RootComponent);
	
	SetActorScale3D(FVector(ActorScale));
}

// Called when the game starts or when spawned
void ACACampfire::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(FireTimer, this, &ACACampfire::FireTick, FireTickInterval, true);

	PlayedFiredSound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSound, GetActorLocation());
}

// Called every frame
void ACACampfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACACampfire::LitBonfire()
{
	ActorScale = 1.f;
	//SetActorScale3D(FVector(ActorScale));
	CampFireFire->SetWorldScale3D(FVector(ActorScale));
}



void ACACampfire::FireTick()
{
	ActorScale -= ShrinkValue;
	//SetActorScale3D(FVector(ActorScale));
	CampFireFire->SetWorldScale3D(FVector(ActorScale));

	if (ActorScale <= 0.f) {
		UE_LOG(LogTemp, Warning, TEXT("Game over"));
		GetWorldTimerManager().ClearTimer(FireTimer);

		if (PlayedFiredSound)
		{
			PlayedFiredSound->Stop();
			EndGame();
		}
	}
}

