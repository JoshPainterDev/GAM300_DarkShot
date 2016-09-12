// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VR_PlayerChaperone.h"
#include "VR_LeftController.generated.h"

UCLASS()
class DARKSHOTVR_API AVR_LeftController : public AActor
{
	GENERATED_BODY()
	
public:	

    // FORWARD DECLERATION
    class AVR_PlayerChaperone;

	// DEFAULT FUNCTIONS
	AVR_LeftController();
	
    virtual void BeginPlay() override;
	
    virtual void Tick( float DeltaSeconds ) override;

    // COLLISION FUNCTIONS
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
    // MY FUNCTIONS
    AVR_PlayerChaperone* GetPlayerChaperone();
    void UpdateLocationAndOrientation();
    // VARIABLES

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UMotionControllerComponent* MControllerLeft;

    UPROPERTY(VisibleAnywhere)
    class USphereComponent* LeftCollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* BowSceneComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class USkeletalMeshComponent* BowMesh;

    UPROPERTY(BlueprintAssignable, Category = "Collision")
    FComponentBeginOverlapSignature OnComponentBeginOverlap;

    FVector ControllerLocation;
    FRotator ControllerOrientation;
};
