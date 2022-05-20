// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Used for bulleting
#include "BaseProjectile.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseWeaponComponent.generated.h"

USTRUCT()
struct FBaseWeaponProperties {
	GENERATED_USTRUCT_BODY()

	UPROPERTY() // Base properties for the projectile
		FBaseProjectileProperties BaseProjectileProperties;

	UPROPERTY() // Rounds per minute 
		float FireRate;

	UPROPERTY() // How much to offset the spawn point of bullets, relative to center of the owning actor
		FVector FireOffset;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDSPOSTRELEASE_API UBaseWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseWeaponComponent();

	void GetLifeTimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() // Called whenever player presses fire button, checks if possible to fire and if so, calles trigger server fire
		virtual void Fire();

	UFUNCTION(Server, Reliable, WithValidation) // called on the player side, tells server to spawn a bullet
		virtual void TriggerServerFire();

	UFUNCTION(NetMulticast, Reliable) // actually fires the bullet
		virtual void Server_Fire();


	virtual void SetBaseWeaponProperties(FBaseWeaponProperties NewWeaponProperties);
	UFUNCTION(BlueprintCallable)
		virtual void SetBaseProjectileToFire(TSubclassOf<ABaseProjectile> NewBaseProjectileToFire);
	virtual void SetFireRate(float NewFireRate);
	virtual void SetFireOffset(FVector NewFireOffset);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	FBaseWeaponProperties BaseWeaponProperties;

	// Time To Next Fire, in seconds
	float TTNF;
	UPROPERTY(EditAnywhere) // What bullet to fire
		TSubclassOf<ABaseProjectile> BaseProjectileToFire;

		
};
