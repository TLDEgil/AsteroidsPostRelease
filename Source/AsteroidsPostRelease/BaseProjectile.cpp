// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

// Include so that I can cast hit actors to this and know that they will have a Register Hit Function
#include "BaseAsteroidsGameActor.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BaseProjectile Spawned"));
	
}

void ABaseProjectile::UpdateLocation(float DeltaTime, FHitResult& HitResult)
{	// * 100 because Velocity is in meters / second, and Unreal measures in CM
	FVector Translation = BaseProjectileProperties.Forwards * DeltaTime * BaseProjectileProperties.Velocity * 100; 
	AddActorWorldOffset(Translation, true, &HitResult);
}


// Called on valid blocking hits, causes hit object to take the damage dealt by this projectile and then marks for destruction
void ABaseProjectile::HandleHit(FHitResult& HitResult)
{
	if (!HitResult.IsValidBlockingHit()) return;
	
	AActor* HitActor = HitResult.GetActor();

	if (HitActor->IsA(ABaseAsteroidsGameActor::StaticClass()))
	{
		Cast<ABaseAsteroidsGameActor>(HitActor)->RegisterHit(BaseProjectileProperties.Damage);
		Destroy();
	}
}

void ABaseProjectile::CheckForDestroy(float DeltaTime)
{
	BaseProjectileProperties.TTL -= DeltaTime; // Reduce Time To Live by how long has been Lived

	
	if (BaseProjectileProperties.TTL < 0) // If too long has been lived
	{
		Destroy(); // Don't live (:
	}
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	UpdateLocation(DeltaTime, Hit);
	HandleHit(Hit);
	CheckForDestroy(DeltaTime);
}

void ABaseProjectile::SetBaseProjectileProperties(FBaseProjectileProperties NewBaseProjectileProperties)
{
	BaseProjectileProperties = NewBaseProjectileProperties;
}

FBaseProjectileProperties ABaseProjectile::GetBaseProjectileProperties()
{
	return BaseProjectileProperties;
}

