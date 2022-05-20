// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseWeaponComponent.h"
#include "BasePlayerPawnMovementComponent.h"
#include "BasePlayerShipPawn.generated.h"

UCLASS()
class ASTEROIDSPOSTRELEASE_API ABasePlayerShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePlayerShipPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
		UBaseWeaponComponent* BaseWeaponComponent;

	UPROPERTY(BlueprintReadWrite)
		UBasePlayerPawnMovementComponent* BaseMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void FireWeapon(float Axisvalue);

	// Calls corrosponding function on the movement component
	UFUNCTION()
		virtual void UpdateTargetThrust(float NewTargetThrust);
	UFUNCTION()
		virtual void UpdateTargetPitch(float NewFargetPitch);
	UFUNCTION()
		virtual void UpdateTargetYaw(float NewTargetYaw);
	UFUNCTION()
		virtual void UpdateTargetRoll(float NewTargetRoll);



};
