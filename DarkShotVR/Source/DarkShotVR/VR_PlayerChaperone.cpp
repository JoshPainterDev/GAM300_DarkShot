// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "VR_PlayerChaperone.h"

#define X_SPACE 20
#define Y_SPACE 20
#define Z_SPACE 20

// Sets default values
AVR_PlayerChaperone::AVR_PlayerChaperone()
{
	PrimaryActorTick.bCanEverTick = true;
    SteamVRChaperone = CreateDefaultSubobject<USteamVRChaperoneComponent>(TEXT("SteamVRChaperone"));
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	arrow = nullptr;
}

// Called when the game starts or when spawned
void AVR_PlayerChaperone::BeginPlay()
{
    GetWorld()->Exec(GetWorld(), TEXT("stereo on"));
    Super::BeginPlay();
}

// Called every frame
void AVR_PlayerChaperone::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);
    if (USteamVRFunctionLibrary::GetTrackedDevicePositionAndOrientation(0, HMDLocation, HMDOrientation))
    {
        
        SetActorRelativeLocation(HMDLocation);
        SetActorRelativeRotation(HMDOrientation);
        SetActorLocation(HMDLocation);
        SetActorRotation(HMDOrientation);
        CameraComp->SetRelativeLocationAndRotation(HMDLocation, HMDOrientation);
        CameraComp->SetWorldLocationAndRotation(HMDLocation, HMDOrientation);
    }
}

// Called to bind functionality to input
void AVR_PlayerChaperone::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
    InputComponent->BindAction("GrabArrow", IE_Pressed, this, &AVR_PlayerChaperone::GrabArrow);
   InputComponent->BindAction("GrabArrow", IE_Released, this, &AVR_PlayerChaperone::FireArrow);
	//Super::SetupPlayerInputComponent(InputComponent);

}

void AVR_PlayerChaperone::GrabArrow()
{
	//if (arrow == nullptr)
		SpawnArrow();
    // check to see if I can grab an arrow
   // SpawnArrow();
    /*
    FVector pos;
    FRotator orientation;
    if (USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Right, pos, orientation))
        if (pos.Z + Z_SPACE > HMDLocation.Z && pos.Z - Z_SPACE < HMDLocation.Z)
            if (pos.X >= HMDLocation.X - 30)
                if (pos.Y >= HMDLocation.Y  - 30 )
                {
                    SpawnArrow();
                    return;
                }*/
}

void AVR_PlayerChaperone::FireArrow()
{

}

void AVR_PlayerChaperone::SpawnArrow()
{
    arrow = (AProjectileArrow*)GetWorld()->SpawnActor<AProjectileArrow>(AProjectileArrow::StaticClass(), HMDLocation, HMDOrientation);
    arrow->current_arrow_state = AProjectileArrow::State::FOLLOW;
}

void AVR_PlayerChaperone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
