// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes") //, meta = (ExposeOnSpawn = "true"))
		float MaxHealth;

	// HealthMax, Stamina, Strength

public:

	// Functions
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsAlive() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetHealth() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsMaxHealth() const;

	UPROPERTY(BlueprintAssignable)
		FOnHealthChanged OnHealthChanged;
	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool ApplyHealthChange(float Delta);



};
