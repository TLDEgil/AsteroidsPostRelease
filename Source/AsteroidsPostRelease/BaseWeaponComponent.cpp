// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponComponent.h"

// Sets default values for this component's properties
UBaseWeaponComponent::UBaseWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetNetAddressable();
	SetIsReplicated(true);
}


// Called when the game starts
void UBaseWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// Ensure that there are paramaters incase the Player Pawn hasn't set any
	BaseWeaponProperties.FireOffset = FVector(500, 0, 0);
	BaseWeaponProperties.FireRate = 60.0f;
	BaseWeaponProperties.BaseProjectileProperties.TTL = 3;
	BaseWeaponProperties.BaseProjectileProperties.Velocity = 500;
	BaseWeaponProperties.BaseProjectileProperties.Damage = 10;
}


void UBaseWeaponComponent::GetLifeTimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Called every frame
void UBaseWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TTNF -= DeltaTime;
}

void UBaseWeaponComponent::Fire()
{
	if (TTNF > 0) return;
	if (!BaseProjectileToFire)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseWeaponComponent on %s has no BaseProjectileToFire set "), *GetOwner()->GetName());
		return;
	}
	// Trigger the Fire function that runs on the server and spawn the bullet
	TriggerServerFire();
	UE_LOG(LogTemp, Warning, TEXT("Fire called by player, calling TriggerServerFire..."));
	TTNF = BaseWeaponProperties.FireRate / 60;

}

void UBaseWeaponComponent::TriggerServerFire_Implementation()
{
	// All this function does is get called from the client, so that Server_Fire can Multicast from the server
	UE_LOG(LogTemp, Warning, TEXT("Fire called TriggerServerFire.... Calling Server_Fire...."));
	Server_Fire();
}
bool UBaseWeaponComponent::TriggerServerFire_Validate()
{
	return true; // TLDR BE LAZY AND FIX LATER
}

void UBaseWeaponComponent::Server_Fire_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Called Server_Fire, creating Bullet...."));
	// No need to check if can fire, that was already checked, so this just spawn the bullet
	ABaseProjectile* NewBullet = GetWorld()->SpawnActor<ABaseProjectile>(BaseProjectileToFire, GetOwner()->GetActorTransform());
	NewBullet->AddActorLocalOffset(BaseWeaponProperties.FireOffset);

	// Set the properties that are unique to each bullet
	BaseWeaponProperties.BaseProjectileProperties.TimeCreated = GetOwner()->GetWorld()->TimeSeconds;
	BaseWeaponProperties.BaseProjectileProperties.Forwards = GetOwner()->GetActorForwardVector();

	// Give the bullet these new properties
	NewBullet->SetBaseProjectileProperties(BaseWeaponProperties.BaseProjectileProperties);
}

void UBaseWeaponComponent::SetBaseWeaponProperties(FBaseWeaponProperties NewWeaponProperties)
{
	BaseWeaponProperties = NewWeaponProperties;
}

void UBaseWeaponComponent::SetBaseProjectileToFire(TSubclassOf<ABaseProjectile> NewBaseProjectileToFire)
{
	BaseProjectileToFire = NewBaseProjectileToFire;
}

void UBaseWeaponComponent::SetFireRate(float NewFireRate)
{
	BaseWeaponProperties.FireRate = NewFireRate / 60;
	TTNF = BaseWeaponProperties.FireRate;
}

void UBaseWeaponComponent::SetFireOffset(FVector NewFireOffset)
{
	BaseWeaponProperties.FireOffset = NewFireOffset;
}

