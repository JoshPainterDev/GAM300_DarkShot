// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "SteamVRFunctionLibrary.h"
#include "VR_PlayerChaperone.h"
#include "VR_RightController.generated.h"

UCLASS()
class DARKSHOTVR_API AVR_RightController : public AActor
{
    GENERATED_BODY()

public:

    UPROPERTY()
    class AVR_PlayerChaperone* VR_PlayerChaperone;
    
    // DEFAULT FUNCTIONS    
    AVR_RightController();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // COLLISION FUNCTIONS
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    // MY FUNCTIONS
	bool CheckForSnappingToBow();

    AVR_PlayerChaperone* GetPlayerChaperone();

    void UpdateLocationAndOrientation();
    // VARIABLES
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UMotionControllerComponent* MControllerRight;	

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UStaticMeshComponent* ControllerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class USphereComponent* RightCollisionComp;

    UPROPERTY(BlueprintAssignable, Category = "Collision")
    FComponentBeginOverlapSignature OnComponentBeginOverlap;

    bool LockArrowToBowLocation;

    FVector ControllerLocation;

    FRotator ControllerOrientation;
};
