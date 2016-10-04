// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "ArrowManager.h"


#define BOWTENSIONSCALAR 55
#define BASEARROWSPEED 400
#define MIDARROWROT FRotator(-90, -5, 0)
#define LEFTARROWROT FRotator(-30, -5, 0)
#define RIGHTARROWROT FRotator(30, -5, 0)
#define MIDARROWLOC FVector(3, -1, -40)
#define LEFTARROWLOC FVector(0, -1, 0)
#define RIGHTARROWLOC FVector(0, -1, 0)
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

void UArrowManager::UpdateArrowPos()
{
	//for (auto i = 0; i < 10; i++)
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, CurrentArrow->GetActorLocation().ToString());


	if (arrowsLoaded == 2)
	{
		RightSplitArrow->SetActorRelativeLocation(FVector(RIGHTARROWLOC.X, MIDARROWLOC.Y, MIDARROWLOC.Z + _bowTension));
		LeftSplitArrow->SetActorRelativeLocation(FVector(LEFTARROWLOC.X, MIDARROWLOC.Y, MIDARROWLOC.Z + _bowTension));
		return;
	}
	else if (arrowsLoaded == 3)
	{
		RightSplitArrow->SetActorRelativeLocation(FVector(RIGHTARROWLOC.X, MIDARROWLOC.Y, MIDARROWLOC.Z + _bowTension));
		LeftSplitArrow->SetActorRelativeLocation(FVector(LEFTARROWLOC.X, MIDARROWLOC.Y, MIDARROWLOC.Z + _bowTension));
		CurrentArrow->SetActorRelativeLocation(FVector(MIDARROWLOC.X, MIDARROWLOC.Y, MIDARROWLOC.Z + _bowTension));
		return;
	}
	else
	{
		CurrentArrow->SetActorRelativeLocation(FVector(MIDARROWLOC.X, MIDARROWLOC.Y, MIDARROWLOC.Z + _bowTension));
	}
}

void UArrowManager::SpawnAndAttachArrow(USceneComponent* R_MotionControllerScene)
{
	auto map = GetBluePrintMap();
	if (_isArrowAttachedToBow == false && _isArrowAttachedToHand == false)
	{
		CurrentArrow = GetWorld()->SpawnActor((*map)[FName("StandardArrow")]->GeneratedClass);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);
		CurrentArrow->AttachToComponent(R_MotionControllerScene, rules);
		FVector arrowOffset = FVector(25.0, 0.0, 0.0);
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
		_toggleEquipment = false;
		// unload equipment
		CurrentArrow->Destroy();
		CurrentArrow = GetWorld()->SpawnActor((*map)[FName("StandardArrow")]->GeneratedClass);

		if (arrowsLoaded == 3)
		{
			RightSplitArrow->Destroy();
			LeftSplitArrow->Destroy();

			RightSplitArrow = GetWorld()->SpawnActor((*map)[FName("ExplosiveArrow")]->GeneratedClass);
			LeftSplitArrow = GetWorld()->SpawnActor((*map)[FName("ExplosiveArrow")]->GeneratedClass);

			AttachToBow(L_MotionControllerScene, 3u);
			return;
		}

		AttachToBow(L_MotionControllerScene, 1u);
	}
	else
	{
		_toggleEquipment = true;
		// load equipment
		switch (EquipmentType)
		{
		case EEquipmentType::EXPLOSIVE:
		{
			CurrentArrow->Destroy();
			CurrentArrow = GetWorld()->SpawnActor((*map)[FName("ExplosiveArrow")]->GeneratedClass);
			
			if (arrowsLoaded == 3)
			{
				RightSplitArrow->Destroy();
				LeftSplitArrow->Destroy();

				RightSplitArrow = GetWorld()->SpawnActor((*map)[FName("ExplosiveArrow")]->GeneratedClass);
				LeftSplitArrow = GetWorld()->SpawnActor((*map)[FName("ExplosiveArrow")]->GeneratedClass);

				AttachToBow(L_MotionControllerScene, 3u);
				return;
			}

			AttachToBow(L_MotionControllerScene, 1u);
		}
		break;

		case EEquipmentType::CORROSIVE:
		{
			CurrentArrow->Destroy();
			CurrentArrow = GetWorld()->SpawnActor((*map)[FName("CorrosiveArrow")]->GeneratedClass);

			if (arrowsLoaded == 3)
			{
				RightSplitArrow->Destroy();
				LeftSplitArrow->Destroy();

				RightSplitArrow = GetWorld()->SpawnActor((*map)[FName("CorrosiveArrow")]->GeneratedClass);
				LeftSplitArrow = GetWorld()->SpawnActor((*map)[FName("CorrosiveArrow")]->GeneratedClass);

				AttachToBow(L_MotionControllerScene, 3u);
				return;
			}

			AttachToBow(L_MotionControllerScene, 1u);
		}
		break;

		case EEquipmentType::TRIPWIRE:
		{
			CurrentArrow->Destroy();

			if (arrowsLoaded == 1)
			{
				//Spawn Right Arrow
				RightSplitArrow = GetWorld()->SpawnActor((*map)[FName("TripHeadArrow")]->GeneratedClass);

				RightSplitArrow->SetActorRelativeLocation(FVector(-1, -1, 0));
				RightSplitArrow->SetActorRelativeRotation(RIGHTARROWROT);
				//Spawn Left Arrow
				LeftSplitArrow = GetWorld()->SpawnActor((*map)[FName("TripTailArrow")]->GeneratedClass);
				LeftSplitArrow->SetActorRelativeLocation(FVector(-1, -1, 0));
				LeftSplitArrow->SetActorRelativeRotation(LEFTARROWROT);
				AttachToBow(L_MotionControllerScene, 2u);
			}
			else if (arrowsLoaded == 3)
			{
				CurrentArrow = GetWorld()->SpawnActor((*map)[FName("TripHeadArrow")]->GeneratedClass);
				//Spawn Right Arrow
				RightSplitArrow = GetWorld()->SpawnActor((*map)[FName("TripTailArrow")]->GeneratedClass);
				//Set transform Right Arrow
				RightSplitArrow->SetActorRelativeLocation(FVector(-1, -1, 0));
				RightSplitArrow->SetActorRelativeRotation(RIGHTARROWROT);
				//Spawn Left Arrow
				LeftSplitArrow = GetWorld()->SpawnActor((*map)[FName("TripTailArrow")]->GeneratedClass);
				//Set transform Left Arrow
				LeftSplitArrow->SetActorRelativeLocation(FVector(-1, -1, 0));
				LeftSplitArrow->SetActorRelativeRotation(LEFTARROWROT);
				AttachToBow(L_MotionControllerScene, 3u);
			}
		}
		break;

		default:
			break;
		}
	}

}

void UArrowManager::ShootArrow()
{
	//reset the equipment loading variable
	_toggleEquipment = false;

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
		velocity.X = BASEARROWSPEED + (_bowTension * BOWTENSIONSCALAR) + abilitySteroid;
		ProjectileMovementComponent->SetVelocityInLocalSpace(velocity);
		break;
	}
}

void UArrowManager::DropArrow()
{
	FDetachmentTransformRules rules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, true);
	CurrentArrow->DetachFromActor(rules);
	_isArrowAttachedToHand = false;
	TArray<UProjectileMovementComponent*> projectile;
	CurrentArrow->GetComponents(projectile);

	for (auto ProjectileMovementComponent : projectile)
	{
		ProjectileMovementComponent->InitialSpeed = 0;
		ProjectileMovementComponent->Activate(true);	
		ProjectileMovementComponent->SetVelocityInLocalSpace(FVector());
		break;
	}
}

void UArrowManager::AttachToBow(USceneComponent* L_MotionControllerScene, unsigned numArrows)
{
	arrowsLoaded = numArrows;

	if (numArrows == 1)
	{
		FDetachmentTransformRules detachment(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true);
		CurrentArrow->DetachFromActor(detachment);
		FAttachmentTransformRules attachment(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		CurrentArrow->AttachToComponent(L_MotionControllerScene, attachment);

		CurrentArrow->SetActorRelativeLocation(MIDARROWLOC);
		CurrentArrow->SetActorRelativeRotation(MIDARROWROT);
	}
	else if (numArrows == 2)
	{
		//Detach all arrows
		FDetachmentTransformRules detachment(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true);
		RightSplitArrow->DetachFromActor(detachment);
		LeftSplitArrow->DetachFromActor(detachment);
		//Attach all arrows
		FAttachmentTransformRules attachment(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		RightSplitArrow->AttachToComponent(L_MotionControllerScene, attachment);
		LeftSplitArrow->AttachToComponent(L_MotionControllerScene, attachment);
		//Set relative transform of Right Arrow
		RightSplitArrow->SetActorRelativeLocation(RIGHTARROWLOC);
		RightSplitArrow->SetActorRelativeRotation(RIGHTARROWROT);
		//Set relative transform of Left Arrow
		LeftSplitArrow->SetActorRelativeLocation(LEFTARROWLOC);
		LeftSplitArrow->SetActorRelativeRotation(LEFTARROWROT);
	}
	else if (numArrows == 3)
	{
		//Detach all arrows
		FDetachmentTransformRules detachment(EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, true);
		CurrentArrow->DetachFromActor(detachment);
		RightSplitArrow->DetachFromActor(detachment);
		LeftSplitArrow->DetachFromActor(detachment);
		//Attach all arrows
		FAttachmentTransformRules attachment(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
		CurrentArrow->AttachToComponent(L_MotionControllerScene, attachment);
		RightSplitArrow->AttachToComponent(L_MotionControllerScene, attachment);
		LeftSplitArrow->AttachToComponent(L_MotionControllerScene, attachment);
		//Set relative transform of Middle Arrow
		CurrentArrow->SetActorRelativeLocation(MIDARROWLOC);
		CurrentArrow->SetActorRelativeRotation(MIDARROWROT);
		//Set relative transform of Right Arrow
		RightSplitArrow->SetActorRelativeLocation(RIGHTARROWLOC);
		RightSplitArrow->SetActorRelativeRotation(RIGHTARROWROT);
		//Set relative transform of Left Arrow
		LeftSplitArrow->SetActorRelativeLocation(LEFTARROWLOC);
		LeftSplitArrow->SetActorRelativeRotation(LEFTARROWROT);
	}

	//for (auto i = 0; i < 10; i++)
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, CurrentArrow->GetActorRotation().ToString());
	//CurrentArrow->AddActorLocalRotation(FRotator(-170, 90, 90));
	//for (auto i = 0; i < 10; i++)
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, CurrentArrow->GetActorRotation().ToString());

	_isArrowAttachedToBow = true;
	_isArrowAttachedToHand = false;
	_justReleased = false;
}




