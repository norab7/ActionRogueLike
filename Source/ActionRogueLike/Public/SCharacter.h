// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USActionComponent;
class USCurrencyComponent;
class USAttributeComponent;
class ASProjectileBase;
class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USInteractionComponent* InteractionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USAttributeComponent* AttributeComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USActionComponent* ActionComponent;

	// Properties
	UPROPERTY(EditAnywhere, Category = "Effects")
		FColor HitFlashColor;
	UPROPERTY(EditAnywhere, Category = "Effects")
		float HitFlashSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName HitFlashColorName;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName HitFlashSpeedName;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName TimeToHitName;

	// Functions
	void MoveForward(float Value);
	void MoveRight(float Value);

	void PrimaryInteract();

	void PrimaryAttack();
	void BlackholeAttack();
	void DashAttack();

	void SprintStart();
	void SprintStop();

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
		void HealSelf(float Amount = 100.f);

};
