// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "ArrowManager.h"

#define BOWTENSIONSCALAR 1000
// Sets default values for this component's properties
UArrowManager::UArrowManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	
	// Find all the arrows that we want to load
	static ConstructorHelpers::FObjectFinder<UBlueprint> StandardArrow(TEXT("Blueprint'/Game/Blueprints/StandardArrow.StandardArrow'"));
	static ConstructorHelpers::FObjectFinder<UBlueprint> ExplosiveArrow(TEXT("Blueprint'/Game/Blueprints/ExplosiveArrow.ExplosiveArrow'"));
	// End of finding arrows

	// Now store them all into a map
	_arrowBlueprints["StandardArrow"] = StandardArrow.Object;
	_arrowBlueprints["ExplosiveArrow"] = ExplosiveArrow.Object;
	_isArrowAttachedToHand = false;
	_isArrowAttachedToBow = false;
	// end of storing

	CurrentArrow = nullptr;
	_toggleEquipment = false;
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

void UArrowManager::SpawnAndAttachArrow(USceneComponent* R_MotionControllerScene)
{
	if (_isArrowAttachedToBow == false && _isArrowAttachedToHand == false)
	{
		CurrentArrow = GetWorld()->SpawnActor(_arrowBlueprints["StandardArrow"]->GeneratedClass);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
		CurrentArrow->AttachToComponent(R_MotionControllerScene, rules);
		_isArrowAttachedToHand = true;
	}

}

void UArrowManager::ToggleEquipment(USceneComponent* L_MotionControllerScene)
{
	if (_isArrowAttachedToBow == false)
		return;
	_toggleEquipment = !_toggleEquipment;
	
	if (_toggleEquipment == false)
	{
		// unload equipment
		CurrentArrow->Destroy();
		CurrentArrow = GetWorld()->SpawnActor(_arrowBlueprints["StandardArrow"]->GeneratedClass);
		AttachToBow(L_MotionControllerScene);
	}
	else
	{
		// load equipment
		switch (EquipmentType)
		{
			case EEquipmentType::EXPLOSIVE:
			{
				CurrentArrow->Destroy();
				CurrentArrow = GetWorld()->SpawnActor(_arrowBlueprints["ExplosiveArrow"]->GeneratedClass);
				AttachToBow(L_MotionControllerScene);
			}
			break;

			case EEquipmentType::CORROSIVE:
			{

			}
			break;

			case EEquipmentType::TRIPWIRE:
			{

			}
			break;

			default:
			break;
		}
	}

}

void UArrowManager::ShootArrow()
{
	FDetachmentTransformRules rules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, true);
	CurrentArrow->DetachFromActor(rules);
	_isArrowAttachedToBow = false;
	TArray<UProjectileMovementComponent*> projectile;

	CurrentArrow->GetComponents(projectile);

	for (auto ProjectileMovementComponent : projectile)
	{
		_justReleased = true;
		ProjectileMovementComponent->Activate(true);
		FVector velocity = CurrentArrow->GetActorForwardVector();
		velocity.X *= _bowTension + BOWTENSIONSCALAR;
		ProjectileMovementComponent->SetVelocityInLocalSpace(velocity);
	}

}

void UArrowManager::AttachToBow(USceneComponent* L_MotionControllerScene)
{
	FDetachmentTransformRules detachment(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true);
	CurrentArrow->DetachFromActor(detachment);
	FAttachmentTransformRules attachment(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
	CurrentArrow->AttachToComponent(L_MotionControllerScene, attachment);
	CurrentArrow->SetActorRelativeLocation(FVector(0, 0, 0));
	CurrentArrow->SetActorRelativeRotation(FRotator(-90, -90, 0));
	_isArrowAttachedToBow = true;
	_isArrowAttachedToHand = false;
	_justReleased = false;
}




