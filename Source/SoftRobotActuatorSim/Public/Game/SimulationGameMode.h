// Copyright Marcin Gałąska, 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimulationGameMode.generated.h"

UCLASS()
class SOFTROBOTACTUATORSIM_API ASimulationGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimulationGameMode(const FObjectInitializer& ObjectInitializer);
};
