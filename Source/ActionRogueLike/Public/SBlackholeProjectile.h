// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SBlackholeProjectile.generated.h"

class URadialForceComponent;
/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API ASBlackholeProjectile : public ASProjectileBase {
	GENERATED_BODY()

public:
	ASBlackholeProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URadialForceComponent* RadialForceComponent;
	UPROPERTY(EditAnywhere)
		float ForceRadius;
	UPROPERTY(EditAnywhere)
		float ForceStrength;

	UFUNCTION()
		void OnDestroyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	virtual void PostInitializeComponents() override;
};
