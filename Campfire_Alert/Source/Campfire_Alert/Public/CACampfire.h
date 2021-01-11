// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CACampfire.generated.h"

class UAudioComponent;
class UParticleSystemComponent;
class UCapsuleComponent;


UCLASS()
class CAMPFIRE_ALERT_API ACACampfire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACACampfire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category  = "Component")
	UParticleSystemComponent* CampFireFire;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCapsuleComponent* CapsuleComp;

	USceneComponent* SceneComp;

	float ActorScale;

	UPROPERTY(EditAnywhere, Category = "FireSettings")
	float FireTickInterval;
	
	UPROPERTY(EditAnywhere, Category = "FireSettings")
	float ShrinkValue;

	UPROPERTY(EditAnywhere, Category = "FireSettings")
	USoundBase* FireSound;

	FTimerHandle FireTimer;

	UAudioComponent* PlayedFiredSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LitBonfire();
	void FireTick();

	UFUNCTION(BluePrintImplementableEvent)
	void EndGame();
};
