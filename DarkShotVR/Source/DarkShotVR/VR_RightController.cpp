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

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
    CollisionComp->InitSphereRadius(5.0f);
  //  CollisionComp->BodyInstance.SetCollisionProfileName("RightMotionController");

    CollisionComp->OnComponentHit.AddDynamic(this, &AVR_RightController::OnHit);
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AVR_RightController::OnOverlapBegin);
    CollisionComp->bGenerateOverlapEvents = true;
    SetActorEnableCollision(true);

    LockArrowToBowLocation = false;
}

// Called when the game starts or when spawned
void AVR_RightController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVR_RightController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    FVector pos;
    FRotator orientation;
    if (LockArrowToBowLocation == false)
    {
        if (USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Right, pos, orientation))
        {
            SetActorLocationAndRotation(pos, orientation);
        }
    }

    else
    {
        AttachToBow();
    }
}

void AVR_RightController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    //for (int i = 0; i < 10; ++i)
     //   GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("OVER LAP BEGAN RIGHT CONTROLLER"));

    
    for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
   {  
        if (Iterator->Get()->GetName() == "VR_PlayerChaperone_0")
        {
            auto i = Cast<AVR_PlayerChaperone>(Iterator->Get());
            if (i->arrow)
                i->arrow->current_arrow_state = AProjectileArrow::AIM;

        }
    }
}

void AVR_RightController::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    //for (int i = 0; i < 10; ++i)
      //  GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("HIT  RIGHT CONTROLLER"));
}

void AVR_RightController::LockArrowToBowLocation()
{
}

