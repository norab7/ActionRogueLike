// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

		// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* BarrelMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URadialForceComponent* RadialForceComponent;

	// Properties
	UPROPERTY(EditAnywhere)
		float ForceRadius;
	UPROPERTY(EditAnywhere)
		float ForceStrength;

	// Functions
	UFUNCTION()
		void OnBarrelHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
