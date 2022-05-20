// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAsteroidsGameActor.h"

// Sets default values
ABaseAsteroidsGameActor::ABaseAsteroidsGameActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseAsteroidsGameActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAsteroidsGameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

