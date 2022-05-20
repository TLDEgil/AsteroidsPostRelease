// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerShipPawn.h"
#include "BaseProjectile.h"
#include "Components/InputComponent.h"

// Sets default values
ABasePlayerShipPawn::ABasePlayerShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseWeaponComponent = CreateDefaultSubobject<UBaseWeaponComponent>(TEXT("BaseWeaponComponent"));
	if (!BaseWeaponComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create BaseWeaponComponent on %s"), *GetName());
		return;
	}
	BaseWeaponComponent->SetBaseProjectileToFire(ABaseProjectile::StaticClass());

	BaseMovementComponent = CreateDefaultSubobject<UBasePlayerPawnMovementComponent>(TEXT("BaseMovementComponent"));
}

// Called when the game starts or when spawned
void ABasePlayerShipPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePlayerShipPawn::FireWeapon(float AxisValue)
{
	// Make sure that Fire is actually being called, and that the axis value isn't micro fluctuating 
	if (AxisValue > KINDA_SMALL_NUMBER)
	{
		if (!BaseWeaponComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("Missing BaseWeaponComponent on %s"), *GetName());
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Bang"));
		BaseWeaponComponent->Fire();
	}
}

// Called every frame
void ABasePlayerShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayerShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("FirePlayerPrimaryWeapon", this, &ABasePlayerShipPawn::FireWeapon);

}

