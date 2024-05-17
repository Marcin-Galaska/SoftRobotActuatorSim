// Copyright Marcin Gałąska, 2024.

#include "Actuator/Actuator.h"

AActuator::AActuator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	ActuatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ActuatorMesh"));
	RootComponent = ActuatorMesh;

	// Set MeshMatrix size
	MeshMatrix.Init(TArray<UStaticMesh*>(), NumberOfPressures);
	for(auto& Row : MeshMatrix)
	{
		Row.Init(nullptr, NumberOfForces);
	}

	// Fill MeshMatrix with mesh assets
	for(uint8 Row = 0; Row < NumberOfPressures; ++Row)
	{
		const uint32 Pressure = Row * 100;
		for(uint8 Force = 0; Force < NumberOfForces; ++Force)
		{
			// Get asset path
			const FString AssetName = FString::FromInt(Pressure) + "_" + FString::FromInt(Force);
			FString AssetPath = "/Script/Engine.StaticMesh'/Game/ActuatorMeshes/" + AssetName + "." + AssetName + "'";
			const TCHAR* AssetCharPath = *AssetPath;

			// Add asset to MeshMatrix
			MeshMatrix[Row].EmplaceAt(Force, ConstructorHelpers::FObjectFinder<UStaticMesh>(AssetCharPath).Object);
		}
	}
}

void AActuator::UpdateMesh()
{
	ActuatorMesh->SetStaticMesh(MeshMatrix[CurrentPressure][CurrentForce]);
}

void AActuator::BeginPlay()
{
	Super::BeginPlay();

	// Set mesh to 0_0
	if(!MeshMatrix.IsEmpty())
	{
		ActuatorMesh->SetStaticMesh(MeshMatrix[0][0]);
	}
}

const FString CurrentPressureString = "Current Pressure: ";
const FString CurrentForceString = "Current Force: ";
void AActuator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Print current parameters on screen
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, CurrentPressureString + FString::FromInt(CurrentPressure * 100) + " Pa");
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, CurrentForceString + FString::FromInt(CurrentForce) + " N");
}

uint8 AActuator::GetCurrentPressure() const
{
	return CurrentPressure;
}

uint8 AActuator::GetCurrentForce() const
{
	return CurrentForce;
}

void AActuator::SetCurrentPressure(const uint8& Value)
{
	if(Value > NumberOfPressures - 1)
	{
		return;
	}
	CurrentPressure = Value;
}

void AActuator::SetCurrentForce(const uint8& Value)
{
	if(Value > NumberOfForces - 1)
	{
		return;
	}
	CurrentForce = Value;
}

