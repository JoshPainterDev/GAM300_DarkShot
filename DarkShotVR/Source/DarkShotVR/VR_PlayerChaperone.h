// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SteamVRChaperoneComponent.h"
#include "SteamVRFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "ArrowManager.h"
#include "VR_PlayerChaperone.generated.h"

class UInputComponent;
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

	// Mesh Components For Motion Controllers
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class USkeletalMeshComponent* VR_Bow;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* VR_RightHand;

	// Dummy Scene Components
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* SteamVRChaperoneScene;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* L_MotionControllerScene;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class USceneComponent* R_MotionControllerScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowManager* _arrowManager;

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

	// Default Functions
	AVR_PlayerChaperone(); // Sets default values for this character's properties
	virtual void BeginPlay() override; // Called when the game starts or when spawned
	virtual void Tick(float DeltaSeconds) override; // Called every frame
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override; // Called to bind functionality to input

	// Helper Functions
	void UpdateChaperone();
	void UpdateLeftMotionController();
	void UpdateRightMotionController();
	void GrabArrow();
	void FireArrow();
	void SpawnArrow();
	void SpawnAndAttachArrowToRightHand();

	UFUNCTION(BlueprintCallable, Category ="ArrowManager")
		void UpdateTension(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category ="ArrowManager")
		float DistanceBetweenRHandAndHMD();
	UFUNCTION(BlueprintCallable, Category = "ArrowManager")
		float DistanceBetweenHands();
	UFUNCTION(BlueprintCallable, Category = "ArrowManager")
		bool AttachToBowOrNot();
	// Collision Event Functions
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// End of COllision Event Functions

private:



};
