// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include <Particles/ParticleSystemComponent.h>

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASDashProjectile::ASDashProjectile() {

	// Properties
	ExplodeDelay = 0.2f;
	TeleportDelay = 0.2f;

}

void ASDashProjectile::BeginPlay() {
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_ExplodeDelay, this, &ASDashProjectile::Explode, ExplodeDelay);
}

void ASDashProjectile::TeleportInstigator() {

	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport)) {
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	}
	Destroy();
}

void ASDashProjectile::Explode_Implementation() {

	// Timers
	GetWorldTimerManager().ClearTimer(TimerHandle_ExplodeDelay);
	FTimerHandle TimerHandle_TeleportInstigator; // Timers that are never cancelled can be local
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportInstigator, this, &ASDashProjectile::TeleportInstigator, TeleportDelay);

	// Effects
	ExplodeEffects();

	// Super::Explode_Implementation();

}


