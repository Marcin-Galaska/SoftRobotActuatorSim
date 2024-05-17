// Copyright Marcin Gałąska, 2024.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS(config=GAME)
class SOFTROBOTACTUATORSIM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);

	// Core functions
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaSeconds) override;

	//Getters
	class USpringArmComponent* GetCameraBoom() const;
	class UCameraComponent* GetFollowCamera() const;

	UFUNCTION(BlueprintCallable, Category = "Player Character|Camera")
		float GetStartingCameraBoomArmLength() const;
	UFUNCTION(BlueprintCallable, Category = "Player Character|Camera")
		FVector GetStartingCameraBoomLocation() const;
	UFUNCTION(BlueprintCallable, Category = "Player Character|Camera")
		FRotator GetStartingCameraBoomRotation() const;
		
protected:
	// Camera transform settings
	UPROPERTY(BlueprintReadOnly, Category = "Player Character|Camera")
		float StartingCameraBoomArmLength;
	UPROPERTY(BlueprintReadOnly, Category = "Player Character|Camera")
		FVector StartingCameraBoomLocation;
	UPROPERTY(BlueprintReadOnly, Category = "Player Character|Camera")
		FRotator StartingCameraBoomRotation;

	// Components
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player Character|Camera")
		USpringArmComponent* CameraBoom;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player Character|Camera")
		UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Player Character|Widgets")
		TSubclassOf<UUserWidget> ScreenCenterDotWidget;
	UUserWidget* ScreenCenterDotWidgetInstance;

	// Enhanced Input
	void HandleMoveActionPressed(const FInputActionValue& Value);
	void HandleLookActionPressed(const FInputActionValue& Value);
	void HandlePrimaryActionPressed();
	void HandleSecondaryActionPressed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* MovementAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* LookingAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* PrimaryAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Actions")
		UInputAction* SecondaryAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Mappings")
		UInputMappingContext* BaseMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input Mappings")
		int32 BaseMappingPriority = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controls|Primary Action")
		float PrimaryActionRange = 100.0f;
	
	// Possession handling
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void PawnClientRestart() override;
};