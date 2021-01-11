// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CACharacter.generated.h"


class UCapsuleComponent;
class ACACampfire;
class UPointLightComponent;

UCLASS()
class CAMPFIRE_ALERT_API ACACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACACharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* FireWoodMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPointLightComponent* FireWoodLight;

	FRotator CurrentRotation;
	bool bIsHoldingWood;
	UCapsuleComponent* CapsuleComp;
	
	void DropWood(ACACampfire* Campfire);
	void DropWood();
	int32 WoodBurned;


	UFUNCTION()
	void OnPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveUp(float Value);
	void MoveDown(float Value);
	void MoveLeft(float Value);
	void MoveRight(float Value);

	void CheckAndSetRotation(float Value);

	UFUNCTION(BlueprintCallable)
	bool isCarryingFirewood();

	UFUNCTION(BlueprintCallable)
	int32 GetBurnedWood();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
