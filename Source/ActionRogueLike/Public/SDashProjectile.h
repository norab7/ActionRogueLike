// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "SDashProjectile.generated.h"

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASProjectileBase {
	GENERATED_BODY()

public:
	ASDashProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void TeleportInstigator();

	virtual void Explode_Implementation() override;

	// Timer
	float ExplodeDelay;
	float TeleportDelay;
	FTimerHandle TimerHandle_ExplodeDelay;

};
