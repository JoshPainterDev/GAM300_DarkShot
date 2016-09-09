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
    // Sets default values for this actor's properties
    AVR_RightController();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;


    UPROPERTY(BlueprintAssignable, Category = "Collision")
        FComponentBeginOverlapSignature OnComponentBeginOverlap;
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    /** called when projectile hits something */
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    void AttachToBow();
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UMotionControllerComponent* MControllerRight;
	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UStaticMeshComponent* ControllerMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class USphereComponent* CollisionComp;

    bool LockArrowToBowLocation;
};
