// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "VR_LeftController.h"
s
// Sets default values
AVR_LeftController::AVR_LeftController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MControllerLeft"));
    MControllerLeft->Hand = EControllerHand::Left;
    BowMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BowMesh"));
	BowSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BowSceneComponent"));
    LeftCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("LeftCollisionComponent"));
	LeftCollisionComp->InitSphereRadius(5.0f);
    //CollisionComp->BodyInstance.SetCollisionProfileName("LeftMotionController");
	LeftCollisionComp->OnComponentHit.AddDynamic(this, &AVR_LeftController::OnHit);
	LeftCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AVR_LeftController::OnOverlapBegin);
	LeftCollisionComp->bGenerateOverlapEvents = true;
    SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void AVR_LeftController::BeginPlay()
{
    VR_PlayerChaperone = GetPlayerChaperone();
	Super::BeginPlay();
}

// Called every frame
void AVR_LeftController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    UpdateLocationAndOrientation();
}

void AVR_LeftController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AVR_LeftController::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

AVR_PlayerChaperone* AVR_LeftController::GetPlayerChaperone()
{
    for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
    {
        if (Iterator->Get()->GetName() == "VR_PlayerChaperone_0")
        {
            return Cast<AVR_PlayerChaperone>(Iterator->Get());
        }
    }

    return nullptr;
}

void AVR_LeftController::UpdateLocationAndOrientation()
{
    if (USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Left, ControllerLocation, ControllerOrientation))
    {
        SetActorLocationAndRotation(ControllerLocation, ControllerOrientation);
    }
}
