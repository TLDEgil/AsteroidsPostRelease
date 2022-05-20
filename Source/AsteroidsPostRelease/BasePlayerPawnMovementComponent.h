// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasePlayerPawnMovementComponent.generated.h"

USTRUCT()
struct FBaseMoveData
{
	GENERATED_USTRUCT_BODY()
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDSPOSTRELEASE_API UBasePlayerPawnMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBasePlayerPawnMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		virtual void UpdateTargetThrust(float NewTargetThrust);
	UFUNCTION()
		virtual void UpdateTargetPitch(float NewFargetPitch);
	UFUNCTION()
		virtual void UpdateTargetYaw(float NewTargetYaw);
	UFUNCTION()
		virtual void UpdateTargetRoll(float NewTargetRoll);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Called every Frame, updates Thrust to move ship in desired direction, or stop motion if no input is given
	virtual void UpdateThrust(float DeltaTime);

	UPROPERTY()
		float CurrentPitchRate;
	UPROPERTY()
		float CurrentYawRate;
	UPROPERTY()
		float CurrentRollRate;
	UPROPERTY()
		float TargetPitchRate;
	UPROPERTY()
		float TargetYawRate;
	UPROPERTY()
		float TargetRollRate;




		
};
