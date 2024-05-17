// Copyright Marcin Gałąska, 2024.

#pragma once

#include "CoreMinimal.h"
#include "Actuator.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "ActuatorControlButton.generated.h"

UCLASS()
class SOFTROBOTACTUATORSIM_API AActuatorControlButton : public AActor
{
	GENERATED_BODY()
	
public:	
	AActuatorControlButton(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintNativeEvent)
		void UpdateActuatorParameters(); 
	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control Button|Collision", meta=(AllowPrivateAccess = "true"))
		UCapsuleComponent* HitCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Button|Actuator", meta=(AllowPrivateAccess = "true"))
		AActuator* Actuator;
	
	virtual void BeginPlay() override;
};
