// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include <Components/SphereComponent.h>

#include "SAttributeComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile() {

	AttackDamage = -10.f;
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && OtherActor != GetInstigator()) {
		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComponent) {
			AttributeComponent->ApplyHealthChange(AttackDamage);
			Explode();
		}
	}
}
