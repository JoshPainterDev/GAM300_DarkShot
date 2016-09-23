// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include <map>
#include "ArrowManager.generated.h"

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	EXPLOSIVE 	UMETA(DisplayName = "EXPLOSIVE"),
	CORROSIVE	UMETA(DisplayName = "CORROSIVE"),
	TRIPWIRE	UMETA(DisplayName = "TRIPWIRE")
};

UENUM(BlueprintType)
enum class EAttunementType : uint8
{
	CONQUEROR 		UMETA(DisplayName = "CONQUEROR"),		
	RAILGUN			UMETA(DisplayName = "RAILGUN"),
	SHARPSHOOTER	UMETA(DisplayName = "SHARPSHOOTER")
};

UENUM(BlueprintType)
enum class EUltimateAbilityType : uint8
{
	EMPCHARGE 			UMETA(DisplayName = "EMPCHARGE"),
	SEARCHANDDESTROY	UMETA(DisplayName = "SEARCHANDDESTROY"),
	SLOWTIME			UMETA(DisplayName = "SLOWTIME")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKSHOTVR_API UArrowManager : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _isArrowAttachedToHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _isArrowAttachedToBow;

	// Bow Animation Information Setup
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _justReleased;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float _bowTension;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EEquipmentType EquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EAttunementType AttunementType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EUltimateAbilityType UltimateAbilityType;


	// Declarations of all Callable Functions useable in blueprints
	UFUNCTION(BlueprintCallable, Category = "ArrowManager")
		void SpawnAndAttachArrow(USceneComponent* R_MotionControllerScene);
	UFUNCTION(BlueprintCallable, Category = "ArrowManager")
		void ToggleEquipment(USceneComponent* L_MotionControllerScene);
	UFUNCTION(BlueprintCallable, Category = "ArrowManager")
		void ShootArrow();

	AActor* CurrentArrow;
	void AttachToBow(USceneComponent* L_MotionControllerScene);
	// Sets default values for this component's properties
	UArrowManager();
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	


private:
	std::map<std::string, UBlueprint*> _arrowBlueprints;
	bool _toggleEquipment; 
};

