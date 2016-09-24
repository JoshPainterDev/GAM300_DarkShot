// Fill out your copyright notice in the Description page of Project Settings.

#include "DarkShotVR.h"
#include "DarkShotVRGameMode.h"
static TMap<FName, UBlueprint *> * s_bluePrintMapPtr = nullptr;

const TMap<FName, UBlueprint *> * GetBluePrintMap()
{
	return s_bluePrintMapPtr;
}

ADarkShotVRGameMode::ADarkShotVRGameMode()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> Player(TEXT("Blueprint'/Game/Player/MyVR_PlayerChaperone.MyVR_PlayerChaperone'"));
	DefaultPawnClass = (UClass*)Player.Object->GeneratedClass;
	// Find all the arrows that we want to load
	static ConstructorHelpers::FObjectFinder<UBlueprint> StandardArrow(TEXT("Blueprint'/Game/Arrows/Blueprints/StandardArrow.StandardArrow'"));
	static ConstructorHelpers::FObjectFinder<UBlueprint> ExplosiveArrow(TEXT("Blueprint'/Game/Arrows/Blueprints/ExplosiveArrow.ExplosiveArrow'"));
	// End of finding arrows

	// Now store them all into a map
	m_bluePrintMap.Add(FName("StandardArrow"),StandardArrow.Object);
	m_bluePrintMap.Add(FName("ExplosiveArrow"), ExplosiveArrow.Object);

	s_bluePrintMapPtr = &m_bluePrintMap;
}

const TMap<FName, UBlueprint *> & ADarkShotVRGameMode::GetBluePrintMap() const
{
	return m_bluePrintMap;
}

