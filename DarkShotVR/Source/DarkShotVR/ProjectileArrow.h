// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectileArrow.generated.h"

UCLASS()
class DARKSHOTVR_API AProjectileArrow : public AActor
{
	GENERATED_BODY()
	
    // Sphere collision component 
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    class USphereComponent* CollisionComp;

    UPROPERTY(VisibleDefaultsOnly)
        class UStaticMeshComponent* StaticMesh;
    /** Projectile movement component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
   class UProjectileMovementComponent* ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	AProjectileArrow();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    
    /** called when projectile hits something */
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    void FollowRightMotionController();
    void SnapToBow();
    // Returns CollisionComp subobject
    FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
    
    // Returns ProjectileMovement subobject 
    FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
    enum State
    {
        FOLLOW,
        AIM,
        SHOOT
    };

    State current_arrow_state;
};
