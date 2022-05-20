// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAsteroidsGameActor.generated.h"

UCLASS()
class ASTEROIDSPOSTRELEASE_API ABaseAsteroidsGameActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAsteroidsGameActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void RegisterHit(float DamageTaken) PURE_VIRTUAL(ABaseAsteroidsGameActor::RegisterHit, return;);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	


};
