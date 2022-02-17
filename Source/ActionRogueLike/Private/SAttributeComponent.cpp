// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SCharacter.h"
#include "SGameModeBase.h"


static TAutoConsoleVariable<float> CVarPlayerDamageMultiplier(TEXT("sl.PlayerDamageMultiplier"), 1.f, TEXT("Global Damage Modifier for Attribute Component on player damage."), ECVF_Cheat);
static TAutoConsoleVariable<float> CVarEnemyDamageMultiplier(TEXT("sl.EnemyDamageMultiplier"), 1.f, TEXT("Global Damage Modifier for Attribute Component on enemy damage."), ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	Health = 100.f;
	MaxHealth = 100.f;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor) {
	if (FromActor) {
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor) {
	USAttributeComponent* AttributeComponent = GetAttributes(Actor);
	if (AttributeComponent) {
		return AttributeComponent->IsAlive();
	}
	return false;
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

float USAttributeComponent::GetMissingHealth() const {
	return MaxHealth - Health;
}

bool USAttributeComponent::IsMaxHealth() const {
	return Health >= MaxHealth;
}

bool USAttributeComponent::Kill(AActor* Instigator) {
	return ApplyHealthChange(Instigator, -GetMaxHealth());
}


bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta) {

	if (!GetOwner()->CanBeDamaged() && Delta < 0.f) {
		return false;
	}

	// CVar Damage Multiplier
	if (Delta < 0.f) {
		float DamageMultiplier = Cast<ASCharacter>(InstigatorActor) ? CVarPlayerDamageMultiplier.GetValueOnGameThread() : CVarEnemyDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);

	float HealthDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, HealthDelta);


	// Died
	if (HealthDelta < 0.f && Health == 0.f) {
		ASGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		GameMode->OnActorKilled(GetOwner(), InstigatorActor);
	}

	return HealthDelta != 0;
}


