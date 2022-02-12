// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, Category = "SCharacter")
		USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "SCharacter")
		UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "SCharacter")
		USInteractionComponent* InteractionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SCharacter")
		USAttributeComponent* AttributeComponent;

	// Properties
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> BlackholeClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> DashClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "Attack")
		float PrimaryAttackDelay;
	UPROPERTY(EditAnywhere, Category = "Attack")
		FColor HitFlashColor;
	UPROPERTY(EditAnywhere, Category = "Attack")
		float HitFlashSpeed;

	// Timers
	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_BlackholeAttack;
	FTimerHandle TimerHandle_DashAttack;

	// Functions
	void MoveForward(float Value);
	void MoveRight(float Value);

	void PrimaryInteract();

	void PrimaryAttack();
	void BlackholeAttack();
	void DashAttack();

	void PrimaryAttackTimeElapsed();
	void BlackholeAttackTimeElapsed();
	void DashAttackTimeElapsed();

	void SpawnProjectile(const TSubclassOf<AActor>& Projectile);

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
