// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	Health = 100.f;
	MaxHealth = 100.f;
}

bool USAttributeComponent::IsAlive() const {
	return Health > 0.f;
}

float USAttributeComponent::GetHealth() const {
	return Health;
}

float USAttributeComponent::GetMaxHealth() const {
	return MaxHealth;
}

bool USAttributeComponent::IsMaxHealth() const {
	return Health >= MaxHealth;
}


bool USAttributeComponent::ApplyHealthChange(float Delta) {
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);

	float HealthDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(nullptr, this, Health, HealthDelta);

	return HealthDelta != 0;
}


