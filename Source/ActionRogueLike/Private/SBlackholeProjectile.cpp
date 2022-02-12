// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackholeProjectile.h"

#include <Components/SphereComponent.h>
#include <PhysicsEngine/RadialForceComponent.h>

ASBlackholeProjectile::ASBlackholeProjectile() {

	// Setup Properties
	ForceRadius = 1000.f;
	ForceStrength = -500000.f;
	bExplodeOnHit = false;

	// Setup RadialForceComponent
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->bImpulseVelChange = false;
	RadialForceComponent->Radius = ForceRadius;
	RadialForceComponent->ForceStrength = ForceStrength;

	// Binds
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASBlackholeProjectile::OnDestroyOverlap);
}

void ASBlackholeProjectile::OnDestroyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, OtherComp: %s"), *OtherActor->GetName(), *OtherComp->GetName());
	if (OtherActor && OtherComp && OtherComp->IsSimulatingPhysics()) {
		OtherActor->Destroy();
	}
}

void ASBlackholeProjectile::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SetLifeSpan(5.f);
}
