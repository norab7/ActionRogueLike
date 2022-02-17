// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"

static TAutoConsoleVariable<bool> CVarPickupCostsActive(TEXT("sl.PickupCostsActive"), true, TEXT("Enabled cost checks for pickup up items."));

// Sets default values
ASHealthPotion::ASHealthPotion() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthValue = 10.f;
	CreditCost = 5;
}


void ASHealthPotion::PawnPickup(APawn* PawnToPickup) {
	Super::PawnPickup(PawnToPickup);

	if (!ensure(PawnToPickup)) {
		return;
	}

	USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(PawnToPickup);
	if (ensure(AttributeComponent) && !AttributeComponent->IsMaxHealth()) {

		if (ASPlayerState* PlayerState = PawnToPickup->GetPlayerState<ASPlayerState>()) {

			if (PlayerState->RemoveCredits(CreditCost) && AttributeComponent->ApplyHealthChange(this, HealthValue)) {

				FTimerHandle TimerHandle_RespawnDelay;
				GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, this, &ASHealthPotion::RespawnPickup, RespawnDelay);


			}
		}
	}
}

void ASHealthPotion::RespawnPickup() {
	Super::RespawnPickup();
}

