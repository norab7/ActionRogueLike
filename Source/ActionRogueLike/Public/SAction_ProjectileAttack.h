// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_ProjectileAttack.generated.h"

class UAnimMontage;
class UParticleSystem;

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API USAction_ProjectileAttack : public USAction {
	GENERATED_BODY()

public:
	USAction_ProjectileAttack();

protected:

	// Base Properties
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackAnimDelay;
	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName HandSocketName;

	// Particle system played during attack animation
	UPROPERTY(EditAnywhere, Category = "Attack")
		UParticleSystem* CastingEffect;


	// Functions
	UFUNCTION()
		void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);

public:
	virtual void StartAction_Implementation(AActor* Instigator) override;
	virtual void StopAction_Implementation(AActor* Instigator) override;

};
