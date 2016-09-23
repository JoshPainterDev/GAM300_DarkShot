// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "ArrowManager.h"


// Sets default values for this component's properties
UArrowManager::UArrowManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	
	// Find all the arrows that we want to load
	static ConstructorHelpers::FObjectFinder<UBlueprint> StandardArrow(TEXT("Blueprint'/Game/Blueprints/StandardArrow.StandardArrow'"));
	// End of finding arrows

	// Now store them all into a map
	_arrowBlueprints["StandardArrow"] = StandardArrow.Object;
	_isArrowAttachedToHand = false;
	_isArrowAttachedToBow = false;
	// end of storing
	// ...
}


// Called when the game starts
void UArrowManager::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UArrowManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	// ...
}

void UArrowManager::SpawnAndAttachArrow()
{
	if (_isArrowAttachedToBow == false && _isArrowAttachedToHand == false)
	{
		auto i = GetWorld()->SpawnActor(_arrowBlueprints["StandardArrow"]->GeneratedClass);
		_isArrowAttachedToHand = true;
	}

}

void UArrowManager::ActivateAbility()
{

}




