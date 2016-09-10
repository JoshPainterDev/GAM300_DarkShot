// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"

#include "SteamVRFunctionLibrary.h"
#include "ProjectileArrow.h"
#include "VR_PlayerChaperone.generated.h"

UCLASS()
class DARKSHOTVR_API AVR_PlayerChaperone : public ACharacter
{
	GENERATED_BODY()
public:
    enum ArrowType
    {

    };

	// Sets default values for this character's properties
	AVR_PlayerChaperone();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( UInputComponent* InputComponent) override;
    
    void GrabArrow();
    
    void FireArrow();
    
    void SpawnArrow();
    UPROPERTY(EditAnywhere, Category = Projectile)
        AProjectileArrow* arrow;

    UFUNCTION()
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
    UPROPERTY(VisibleAnywhere)
        class USteamVRChaperoneComponent* SteamVRChaperone;

    UPROPERTY(VisibleAnywhere, Category = "Components")
        class UCameraComponent* CameraComp;



    FVector HMDLocation;
    FRotator HMDOrientation;
};
