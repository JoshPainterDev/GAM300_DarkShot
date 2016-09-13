// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "ProjectileArrow.h"


// Sets default values
AProjectileArrow::AProjectileArrow()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	ArrowSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ArrowSceneComponent"));
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("ArrowCollisionSphere"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("StaticMesh'/Game/ViveMaterials/arrowTest_01.arrowTest_01'"));

	StaticMesh->SetStaticMesh(SphereVisualAsset.Object);
	current_arrow_state = FOLLOW;
	isAttachedToBow = false;
}

// Called when the game starts or when spawned
void AProjectileArrow::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName() == "VR_LeftController_1")
		{
			BowScene = ActorItr->FindComponentByClass<USceneComponent>();
			break;
		}
	}

		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName() == "VR_RightController_1")
		{
			RightController = *ActorItr;
			RightScene = ActorItr->FindComponentByClass<USceneComponent>();
			RightMesh = ActorItr->FindComponentByClass<UStaticMeshComponent>();
			break;
		}
	}

}

// Called every frame
void AProjectileArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	switch (current_arrow_state)
	{
	case FOLLOW:
		FollowRightMotionController();
		break;
	case AIM:
		//   SnapToBow();
		break;
	case SHOOT:
		this->Destroy(true);
		break;
	}*/
}


void AProjectileArrow::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	for (int i = 0; i < 2000; ++i)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("COLLISION DETECTED"));
}

void AProjectileArrow::FollowRightMotionController()
{
	FVector pos;
	FRotator orientation;
	if (USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Right, pos, orientation))
	{
		SetActorLocationAndRotation(pos, orientation);
	}

}
void AProjectileArrow::SnapToLeftHand()
{
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	AttachToComponent(RightScene, rules);
	FRotator r;
	r.Pitch = -90;
	FVector l;
	l.X += 60;
	SetActorRelativeLocation(l);
	RightMesh->ToggleVisibility();
}
void AProjectileArrow::ShootArrow()
{
	if (isAttachedToBow)
	{
		FDetachmentTransformRules rules(EDetachmentRule::KeepWorld, true);
		DetachAllSceneComponents(BowScene, rules);
		RightMesh->ToggleVisibility();
	}
	
	else
	{
		FDetachmentTransformRules rules(EDetachmentRule::KeepWorld, true);
		DetachAllSceneComponents(RightScene, rules);
	}

	float distance = DistanceBetweenHands();
	FName compname("Projectile");
	ProjectileMovement = ConstructObject<UProjectileMovementComponent>(UProjectileMovementComponent::StaticClass(), this, compname);
	if (ProjectileMovement)
	{
		CollisionComp->IgnoreActorWhenMoving(RightController, true);
		ProjectileMovement->UpdatedComponent = CollisionComp;
		ProjectileMovement->InitialSpeed = 3000.f;
		ProjectileMovement->MaxSpeed = 3000.f;	
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = true;
		ProjectileMovement->RegisterComponent();
		
	}
	//ProjectileMovement = ConstructObject<UProjectileMovementComponent>(UProjectileMovementComponent::StaticClass(), this, GetName());
}
float AProjectileArrow::DistanceBetweenHands()
{
	FVector rightpos;
	FRotator rightorientation;
	FVector lefthand_pos;
	FRotator lefthand_orientation;
	USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Right, rightpos, rightorientation);
	USteamVRFunctionLibrary::GetHandPositionAndOrientation(0, EControllerHand::Left, lefthand_pos, lefthand_orientation);

	float x = rightpos.X - lefthand_pos.X;
	float y = rightpos.Y - lefthand_pos.Y;
	float z = rightpos.Z - lefthand_pos.Z;


	return sqrt((x*x) + (y*y) + (z*z));

}
void AProjectileArrow::SnapToBow()
{
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	AttachToComponent(BowScene, rules);
	FRotator r;
	r.Pitch = -90;
	FVector l;
	l.Z += 45;
	SetActorRelativeLocation(l);
	SetActorRelativeRotation(r);
	RightMesh->ToggleVisibility();
	isAttachedToBow = true;
}