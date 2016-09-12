// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "VR_RightController.h"


// Sets default values
AVR_RightController::AVR_RightController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MControllerRight"));
    MControllerRight->Hand = EControllerHand::Right;
    ControllerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

    RightCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("RightCollisionComponent"));
	RightCollisionComp->InitSphereRadius(5.0f);
  //  CollisionComp->BodyInstance.SetCollisionProfileName("RightMotionController");

	RightCollisionComp->OnComponentHit.AddDynamic(this, &AVR_RightController::OnHit);
	RightCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AVR_RightController::OnOverlapBegin);
	RightCollisionComp->bGenerateOverlapEvents = true;
    SetActorEnableCollision(true);
    LockArrowToBowLocation = false;
}

// Called when the game starts or when spawned
void AVR_RightController::BeginPlay()
{
	for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
	{
		if (Iterator->Get()->GetName() == "VR_PlayerChaperone_0")
		{
			VR_PlayerChaperone = Cast<AVR_PlayerChaperone>(Iterator->Get());
		}
	}
	Super::BeginPlay();
	
}

// Called every frame
void AVR_RightController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector righthand_pos;
	FRotator righthand_orientation;

	if (USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Right, righthand_pos, righthand_orientation))
	{
		if (VR_PlayerChaperone->arrow)
		{
			if (CheckForSnappingToBow())
			{
				VR_PlayerChaperone->arrow->current_arrow_state = AProjectileArrow::State::AIM;
				VR_PlayerChaperone->arrow->SnapToBow();
			}
		}
		else
			SetActorLocationAndRotation(righthand_pos, righthand_orientation);
	}
}
bool AVR_RightController::CheckForSnappingToBow()
{
	FVector righthand_pos;
	FRotator righthand_orientation;
	FVector lefthand_pos;
	FRotator lefthand_orientation;

	USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Right, righthand_pos, righthand_orientation);
	USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Left, lefthand_pos, lefthand_orientation);
	float x = righthand_pos.X - lefthand_pos.X;
	float y = righthand_pos.Y - lefthand_pos.Y;
	float z = righthand_pos.Z - lefthand_pos.Z;


	float distance_between_points = sqrt((x*x) + (y*y) + (z*z));

	if (distance_between_points <= 30)
		return true;
	
	return false;
}
void AVR_RightController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AVR_RightController::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    //for (int i = 0; i < 10; ++i)
      //  GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("HIT  RIGHT CONTROLLER"));
}


