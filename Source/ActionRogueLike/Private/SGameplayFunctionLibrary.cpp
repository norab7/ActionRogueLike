// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

#include "SAttributeComponent.h"

bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount) {
	USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(TargetActor);
	if (AttributeComponent) {
		return AttributeComponent->ApplyHealthChange(DamageCauser, -DamageAmount);
	}
	return false;
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult) {

	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount)) {
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();

		if (HitComponent && HitComponent->IsSimulatingPhysics(HitResult.BoneName)) {

			// Direction is Target - Origin
			FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
			Direction.Normalize();

			HitComponent->AddImpulseAtLocation(Direction * 300000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}
	return false;
}
