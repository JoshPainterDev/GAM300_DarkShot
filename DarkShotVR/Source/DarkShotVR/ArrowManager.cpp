// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "ArrowManager.h"


#define BOWTENSIONSCALAR 42
#define BASEARROWSPEED 400
// Sets default values for this component's properties
UArrowManager::UArrowManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;


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
void UArrowManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UArrowManager::SpawnAndAttachArrow(USceneComponent* R_MotionControllerScene)
{
	auto map = GetBluePrintMap();
	if (_isArrowAttachedToBow == false && _isArrowAttachedToHand == false)
	{
		CurrentArrow = GetWorld()->SpawnActor((*map)[FName("StandardArrow")]->GeneratedClass);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
		CurrentArrow->AttachToComponent(R_MotionControllerScene, rules);
		FVector arrowOffset = FVector(30.0, 0.0, 0.0);
		CurrentArrow->SetActorRelativeLocation(arrowOffset, false);
		FRotator arrowRotation = FRotator(0.0, 0.0, -90.0);
		CurrentArrow->SetActorRelativeRotation(arrowRotation, false);
		_isArrowAttachedToHand = true;
	}

}

void UArrowManager::ToggleEquipment(USceneComponent* L_MotionControllerScene)
{
	if (_isArrowAttachedToBow == false)
		return;
	_toggleEquipment = !_toggleEquipment;
	auto map = GetBluePrintMap();
	if (_toggleEquipment == false)
	{
		// unload equipment
		CurrentArrow->Destroy();
		CurrentArrow = GetWorld()->SpawnActor((*map)[FName("StandardArrow")]->GeneratedClass);
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
			CurrentArrow = GetWorld()->SpawnActor((*map)[FName("ExplosiveArrow")]->GeneratedClass);
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
		ProjectileMovementComponent->Activate(true);
		_justReleased = true;
		FVector velocity = CurrentArrow->GetActorForwardVector();
		velocity.X = FMath::Abs(velocity.X);
		velocity.Y = FMath::Abs(velocity.Y);
		velocity.Z = FMath::Abs(velocity.Z);
		velocity.X = BASEARROWSPEED + (_bowTension * BOWTENSIONSCALAR);
		for (auto i = 0; i < 20; i++)
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::FromInt(_bowTension));
		ProjectileMovementComponent->SetVelocityInLocalSpace(velocity);
		break;
	}
}

void UArrowManager::AttachToBow(USceneComponent* L_MotionControllerScene)
{
	FDetachmentTransformRules detachment(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true);
	CurrentArrow->DetachFromActor(detachment);
	FAttachmentTransformRules attachment(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	CurrentArrow->AttachToComponent(L_MotionControllerScene, attachment);
	CurrentArrow->SetActorRelativeLocation(FVector(1, 0, 0));
	CurrentArrow->SetActorRelativeRotation(FRotator(-90, 0, 0));
	_isArrowAttachedToBow = true;
	_isArrowAttachedToHand = false;
	_justReleased = false;
}




