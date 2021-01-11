// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAFireWood.generated.h"

class UBoxComponent;
class USceneComponent;
class URotatingMovementComponent;

UCLASS()
class CAMPFIRE_ALERT_API ACAFireWood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAFireWood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
	USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp")
	URotatingMovementComponent* RotatingMovementComp;

	
	void RespawnSpawnWood();
	void RespawnTick();
	FTimerHandle TimerHandle_RespawnTick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireSettings")
	int32 TimeToRespawnMin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FireSettings")
	int32 TimeToRespawnMax;

	int32 TimeToRespawn;

	int32 TicksProcessed;

		

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnPickUp();
};
