// Fill out your copyright notice in the Description page of Project Settings.


#include "CACharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CACampfire.h"
#include "CAFireWood.h"
#include "Components/PointLightComponent.h"


// Sets default values
ACACharacter::ACACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsHoldingWood = false;
	CurrentRotation = GetActorRotation();
	CapsuleComp = GetCapsuleComponent();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ACACharacter::OnPickup);

	FireWoodMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireWoodMeshComp"));
	FireWoodMeshComp->SetVisibility(false);
	FireWoodMeshComp->SetupAttachment(RootComponent);

	FireWoodLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("FireWoodLight"));
	FireWoodLight->SetupAttachment(RootComponent);
	FireWoodLight->SetVisibility(false);

	WoodBurned = 0;
}


// Called when the game starts or when spawned
void ACACharacter::BeginPlay()
{
	Super::BeginPlay();	
}

int32 ACACharacter::GetBurnedWood()
{
	return WoodBurned;
}


void ACACharacter::DropWood()
{
	bIsHoldingWood = false;
	FireWoodMeshComp->SetVisibility(bIsHoldingWood);
	FireWoodLight->SetVisibility(bIsHoldingWood);
}

void ACACharacter::DropWood(ACACampfire * Campfire)
{
	DropWood();
	Campfire->LitBonfire();
	WoodBurned++;
}

void ACACharacter::OnPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));

	if (IsPlayerControlled() && OtherActor->ActorHasTag(FName("FireWood")) && !bIsHoldingWood)
	{
		ACAFireWood* FireWood = Cast<ACAFireWood>(OtherActor);
		FireWood->OnPickUp();
		
		bIsHoldingWood = true;
		FireWoodMeshComp->SetVisibility(bIsHoldingWood);
		FireWoodLight->SetVisibility(bIsHoldingWood);
		
	}

	if (OtherActor->ActorHasTag(FName("CampFire")))
	{
		if (bIsHoldingWood)
		{
			ACACampfire* Fire = Cast<ACACampfire>(OtherActor);
			DropWood(Fire);
		}
	}

	if (OtherActor->ActorHasTag(FName("Enemy")))
	{
		UE_LOG(LogTemp, Warning, TEXT("ENEMY OVERLAP"));
		DropWood();
	}
}


// Called every frame
void ACACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void ACACharacter::MoveUp(float Value)
{
	FVector Direction = FVector(1, 0, 0);
	AddMovementInput(Direction * Value);

	CheckAndSetRotation(Value);
}

void ACACharacter::MoveDown(float Value)
{
	FVector Direction = FVector(-1, 0, 0);
	AddMovementInput(Direction * Value);

	CheckAndSetRotation(Value);
}

void ACACharacter::MoveLeft(float Value)
{
	FVector Direction = FVector(0, -1, 0);
	AddMovementInput(Direction * Value);

	CheckAndSetRotation(Value);
}

void ACACharacter::MoveRight(float Value)
{
	FVector Direction = FVector(0, 1, 0);
	AddMovementInput(Direction * Value);

	CheckAndSetRotation(Value);
}

void ACACharacter::CheckAndSetRotation(float Value)
{
	/*if (Value > 0)
	{
		FRotator NewRotation = GetVelocity().Rotation();

		if (NewRotation != CurrentRotation)
		{
			SetActorRotation(GetVelocity().Rotation());
			CurrentRotation = NewRotation;
		}
	}*/
}

bool ACACharacter::isCarryingFirewood()
{
	return bIsHoldingWood;
}



// Called to bind functionality to input
void ACACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveUp", this, &ACACharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveDown", this, &ACACharacter::MoveDown);
	PlayerInputComponent->BindAxis("MoveLeft", this, &ACACharacter::MoveLeft);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACACharacter::MoveRight);
}