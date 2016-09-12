// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "VR_LeftController.h"


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
	Super::BeginPlay();
	
}

// Called every frame
void AVR_LeftController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    FVector pos;
    FRotator orientation;
    if (USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Left, pos, orientation))
    {
        SetActorLocationAndRotation(pos, orientation);
    }
}

void AVR_LeftController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
   /* for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
    {
        FString s = Iterator->Get()->GetName();
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, s);
        if ( s == "VR_PlayerChaperone_0")
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("VR_PlayerChaperone")); //i = 0; Iterator->Get(//->arrow->current_arrow_state = AProjectileArrow::State::AIM;
    }*/
}

void AVR_LeftController::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}
