// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VR_PlayerChaperone.h"
#include "StandardArrow.generated.h"
UCLASS()
class DARKSHOTVR_API AStandardArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	class AVR_PlayerChaperone* VR_Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR_PlayerInfo)
		bool _AttachedToHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR_PlayerInfo)
		bool _AttachedToBow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR_PlayerInfo)
		class USceneComponent* L_MotionControllerScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR_PlayerInfo)
		class USceneComponent* R_MotionControllerScene;
	// Sets default values for this actor's properties
	AStandardArrow();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
