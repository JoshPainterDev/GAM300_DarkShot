// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "StandardArrow.h"


// Sets default values
AStandardArrow::AStandardArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStandardArrow::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStandardArrow::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

