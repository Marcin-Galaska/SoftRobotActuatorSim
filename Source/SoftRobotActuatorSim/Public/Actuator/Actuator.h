// Copyright Marcin Gałąska, 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actuator.generated.h"

UCLASS()
class SOFTROBOTACTUATORSIM_API AActuator : public AActor
{
	GENERATED_BODY()
	
public:	
	AActuator(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		void UpdateMesh();

	UFUNCTION(BlueprintCallable)
		uint8 GetCurrentPressure() const;
	UFUNCTION(BlueprintCallable)
		uint8 GetCurrentForce() const;
	UFUNCTION(BlueprintCallable)
		void SetCurrentPressure(const uint8& Value);
	UFUNCTION(BlueprintCallable)
		void SetCurrentForce(const uint8& Value);

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actuator|Mesh", meta=(AllowPrivateAccess = "true"))
		UStaticMeshComponent* ActuatorMesh;
	
	virtual void BeginPlay() override;

private:
	uint8 CurrentPressure = 0;
	uint8 CurrentForce = 0;
	
	const uint8 NumberOfPressures = 25;
	const uint8 NumberOfForces = 25;

	TArray<TArray<UStaticMesh*>> MeshMatrix;
};
