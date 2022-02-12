// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"


// Sets default values
ASHealthPotion::ASHealthPotion() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthValue = 10.f;

}


void ASHealthPotion::PawnPickup(APawn* PawnToPickup) {
	Super::PawnPickup(PawnToPickup);

	if (ensure(PawnToPickup)) {
		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(PawnToPickup->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (ensure(AttributeComponent) && !AttributeComponent->IsMaxHealth()) {

			FTimerHandle TimerHandle_RespawnDelay;
			GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, this, &ASHealthPotion::RespawnPickup, RespawnDelay);

			AttributeComponent->ApplyHealthChange(HealthValue);

		}
	}
}

void ASHealthPotion::RespawnPickup() {
	Super::RespawnPickup();
}

