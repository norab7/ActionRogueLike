// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPickupBase.generated.h"

class USphereComponent;
UCLASS()
class ACTIONROGUELIKE_API ASPickupBase : public AActor, public ISGameplayInterface {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASPickupBase();

	UPROPERTY(VisibleAnywhere, Category = "PickupBase")
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, Category = "PickupBase")
		USphereComponent* SphereComponent;

protected:

	// Properties
	float SphereRadius;
	float RespawnDelay;

	// Functions
	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PawnPickup(APawn* PawnToPickup);
	virtual void SetPickupActiveState(bool bSetPickupActive);
	virtual void RespawnPickup();

public:
	virtual void PostInitializeComponents() override;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
