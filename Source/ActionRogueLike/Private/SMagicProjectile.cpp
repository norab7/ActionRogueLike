// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include <Components/SphereComponent.h>
#include "SActionEffect.h"
#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile() {

	AttackDamage = 20.f;
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor && OtherActor != GetInstigator()) {

		// Check for Parrying Attack
		USActionComponent* ActionComponent = Cast<USActionComponent>(OtherActor->GetComponentByClass(USActionComponent::StaticClass()));
		if (ActionComponent && ActionComponent->ActiveGameplayTags.HasTag(ParryTag)) {
			ProjectileMovementComponent->Velocity = -ProjectileMovementComponent->Velocity;
			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		// Apply Damage
		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, AttackDamage, SweepResult)) {
			Explode();

			if (ActionComponent) {
				ActionComponent->AddAction(GetInstigator(), BurningActionClass);
			}
		}


	}
}
