// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter {
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere, Category = "Attack")
		float PrimaryAttackDelay;

	
	FTimerHandle TimerHandle_PrimaryAttack;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "SCharacter")
		USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "SCharacter")
		UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "SCharacter")
		USInteractionComponent* InteractionComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void PrimaryAttackTimeElapsed();
	void PrimaryInteract();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
