// Copyright Marcin Gałąska, 2024.

#include "Actuator/ActuatorControlButton.h"

AActuatorControlButton::AActuatorControlButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	HitCapsule = CreateDefaultSubobject<UCapsuleComponent>(FName("HitCapsule"));
	HitCapsule->SetCapsuleRadius(4.0f);
	HitCapsule->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = HitCapsule;
}

void AActuatorControlButton::BeginPlay()
{
	Super::BeginPlay();
}

void AActuatorControlButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActuatorControlButton::UpdateActuatorParameters_Implementation()
{
	check(Actuator);
	
	Actuator->SetCurrentForce(0);
	Actuator->SetCurrentPressure(0);

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Default void AActuatorControlButton::UpdateActuatorParameters_Implementation() called."));
	UE_LOG(LogTemp, Warning, TEXT("Default void AActuatorControlButton::UpdateActuatorParameters_Implementation() called."));
}

