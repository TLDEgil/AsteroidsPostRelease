// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"


USTRUCT() // Holds basic properties of a physically simulated projectile
struct FBaseProjectileProperties 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY() // When the projectile was created
		float TimeCreated;

	UPROPERTY() // Time To Live, in seconds
		float TTL;

	UPROPERTY() // Speed of projectile, in meters per second
		float Velocity;

	UPROPERTY() // Damage dealt upon a hit
		float Damage;

	UPROPERTY() // Direction of mevment of the projectile, to be multiplied by Velocity
		FVector MovementVector;

	UPROPERTY() // The direction the projectile is facing
		FVector Forwards;
};

UCLASS()
class ASTEROIDSPOSTRELEASE_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBaseProjectileProperties(FBaseProjectileProperties NewBaseProjectileProperties);
	FBaseProjectileProperties GetBaseProjectileProperties();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// The core of this class, holds all the basic properties for a basic, physics based projectile
	FBaseProjectileProperties BaseProjectileProperties;

	virtual void UpdateLocation(float DeltaTime, FHitResult& HitResult);
	virtual void HandleHit(FHitResult& HitResult);
	virtual void CheckForDestroy(float DeltaTime);

};
