// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SteamVRChaperoneComponent.h"
#include "SteamVRFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "VR_PlayerChaperone.generated.h"

class UInputComponent;
class AStandardArrow;
UCLASS()
class DARKSHOTVR_API AVR_PlayerChaperone : public ACharacter
{
	GENERATED_BODY()
public:

	// Steam VR Vive Components
	UPROPERTY(VisibleAnywhere)
		class USteamVRChaperoneComponent* SteamVRChaperone;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* FirstPersonCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMotionControllerComponent* L_MotionController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMotionControllerComponent* R_MotionController;
	// End of Steam VR Vive Components

	// Mesh Components For Motion Controllers
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class USkeletalMeshComponent* VR_Bow;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* VR_RightHand;
	// End of Mesh Components For Motion Controllers

	// Dummy Scene Components
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* SteamVRChaperoneScene;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* L_MotionControllerScene;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* R_MotionControllerScene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBlueprint* Arrow;
	// End of Dummy Scene Components

	// Arrow Projectile Class Setup and All Info Necessary for Shooting Arrows
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AStandardArrow> _ArrowToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _isArrowAttachedToHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _isArrowAttachedToBow;
	// End of Arrow Projectile Class Setup


	// Bow Animation Information Setup
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _justReleased;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float _bowTension;
	// End of Bow Animation Information 

	// Struct used to store all the information needed for location and rotation
	struct ViveInfo
	{
		FVector Chaperone_Location;
		FRotator Chaperone_Rotation;

		FVector Left_Location;
		FRotator Left_Rotation;

		FVector Right_Location;
		FRotator Right_Rotation;
	};
	ViveInfo _vive;
	// End of Struct information and declaration for ViveInfo

	// Default Functions
	AVR_PlayerChaperone(); // Sets default values for this character's properties
	virtual void BeginPlay() override; // Called when the game starts or when spawned
	virtual void Tick(float DeltaSeconds) override; // Called every frame
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override; // Called to bind functionality to input
	// End of Virtual Default Functions

	// Helper Functions
	void UpdateChaperone();
	void UpdateLeftMotionController();
	void UpdateRightMotionController();
	void GrabArrow();
	void FireArrow();
	void SpawnArrow();
	void SpawnAndAttachArrowToRightHand();
	// End of Helper Functions

	// Collision Event Functions
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// End of COllision Event Functions

private:



};
