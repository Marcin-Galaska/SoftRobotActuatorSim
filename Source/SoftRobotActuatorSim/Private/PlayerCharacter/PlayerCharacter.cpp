// Copyright Marcin Gałąska, 2024.

#include "PlayerCharacter/PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actuator/ActuatorControlButton.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0,0,70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Save starting camera settings
	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
	StartingCameraBoomRotation = CameraBoom->GetComponentRotation();

	// Add ScreenCenterDot widget to viewport
	if(ScreenCenterDotWidget)
	{
		ScreenCenterDotWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScreenCenterDotWidget);
		ScreenCenterDotWidgetInstance->AddToViewport();
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	if(UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(PrimaryAction)
			PlayerEnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandlePrimaryActionPressed);

		if(SecondaryAction)
			PlayerEnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleSecondaryActionPressed);

		if(MovementAction)
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleMoveActionPressed);

		if(LookingAction)
			PlayerEnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleLookActionPressed);
	}
}

void APlayerCharacter::HandleMoveActionPressed(const FInputActionValue& Value)
{
	if(Value.GetMagnitude() != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value[1]);
		AddMovementInput(GetActorRightVector(), Value[0]);
	}
}

void APlayerCharacter::HandleLookActionPressed(const FInputActionValue& Value)
{
	if(Value.GetMagnitude() != 0.0f)
	{
		AddControllerPitchInput(-1.0f * Value[1]);
		AddControllerYawInput(Value[0]);
	}
}

void APlayerCharacter::HandlePrimaryActionPressed()
{
	// Get Camera location and its look at location within PrimaryActionRange
	const FVector InstigatorLocation = FollowCamera->GetComponentLocation();
	const FVector TargetLocation = FollowCamera->GetComponentRotation().Vector() * PrimaryActionRange + FollowCamera->GetComponentLocation();

	// Set line trace params
	FCollisionQueryParams LineTraceParams = FCollisionQueryParams(FName(TEXT("PlayerCharacterPrimaryAction")), true, this);
	LineTraceParams.bTraceComplex = true;
	LineTraceParams.bReturnPhysicalMaterial = false;
	
	const TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldDynamic;

	// Perform line trace
	FHitResult LineTraceResult(ForceInit);
	GetWorld()->LineTraceSingleByChannel
	(
		LineTraceResult,
		InstigatorLocation,
		TargetLocation,
		CollisionChannel,
		LineTraceParams
	);

	// Check for control button and update parameters on success
	if(auto ButtonActor = Cast<AActuatorControlButton>(LineTraceResult.GetActor()))
	{
		ButtonActor->UpdateActuatorParameters();
	}
}

void APlayerCharacter::HandleSecondaryActionPressed()
{
	// Nothing
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void APlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values outprioritize lower values
			Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
		}
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

USpringArmComponent* APlayerCharacter::GetCameraBoom() const
{
	return CameraBoom;
}

UCameraComponent* APlayerCharacter::GetFollowCamera() const
{
	return FollowCamera;
}

float APlayerCharacter::GetStartingCameraBoomArmLength() const
{
	return StartingCameraBoomArmLength;
}

FVector APlayerCharacter::GetStartingCameraBoomLocation() const
{
	return StartingCameraBoomLocation;
}

FRotator APlayerCharacter::GetStartingCameraBoomRotation() const
{
	return StartingCameraBoomRotation;
}

