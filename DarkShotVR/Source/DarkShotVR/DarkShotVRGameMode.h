// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"

#include "DarkShotVRGameMode.generated.h"

/**
 * 
 */
class UBlueprint;

const TMap<FName, UBlueprint *> * GetBluePrintMap();


UCLASS()
class DARKSHOTVR_API ADarkShotVRGameMode : public AGameMode
{
	
	GENERATED_BODY()

	ADarkShotVRGameMode();
	
	const TMap<FName, UBlueprint *> & GetBluePrintMap() const;
private:
	TMap<FName, UBlueprint *> m_bluePrintMap;
};
