// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include <SGameplayInterface.h>

#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("sl.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component"), ECVF_Cheat);


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1f;

	// ...

	InteractionDistance = 1000.f;

}


void USInteractionComponent::FindBestInteractable() {

	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * InteractionDistance);

	TArray<FHitResult> Hits;
	FCollisionShape CollisionShape;
	float SphereRadius = 30.f;
	CollisionShape.SetSphere(SphereRadius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, CollisionShape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits) {
		if (bDebugDraw) {
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, SphereRadius, 12, LineColor, false, 2.f);
		}

		AActor* HitActor = Hit.GetActor();
		if (HitActor) {
			if (HitActor->Implements<USGameplayInterface>()) {
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (bDebugDraw) {
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);
	}

}

void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FindBestInteractable();

}

void USInteractionComponent::PrimaryInteract() {

	//APawn* MyPawn = Cast<APawn>(MyOwner);
	//ISGameplayInterface::Execute_Interact(HitActor, MyPawn);

}

