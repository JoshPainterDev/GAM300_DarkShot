// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectileArrow.generated.h"

UCLASS()
class DARKSHOTVR_API AProjectileArrow : public AActor
{
	GENERATED_BODY()
	
public:	
    // DEFAULT FUNCTIONS
	AProjectileArrow();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;
    
    // COLLISION FUNCTIONS
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // MY FUNCTIONS
    bool CheckForSnappingToBow();

    AVR_PlayerChaperone* GetPlayerChaperone();

    void FollowRightMotionController();

    void SnapToBow();

    void ParentObject();

    void UpdateRelativeLocationAndOrientation();

    USceneComponent* GetBowSceneComponent();

    FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }

    FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
    // VARIABLES AND ENUMS
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class USceneComponent* ArrowSceneComponent;

    USceneComponent* BowScene;

    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    class USphereComponent* CollisionComp;

    UPROPERTY(VisibleDefaultsOnly)
    class UStaticMeshComponent* StaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
    class UProjectileMovementComponent* ProjectileMovement;

    enum State
    {
        FOLLOW,
        AIM,
        SHOOT
    };

    State current_arrow_state;
};
