// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickupBase.h"
#include "SHealthPotion.generated.h"

class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASPickupBase {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASHealthPotion();

protected:

	UPROPERTY(EditDefaultsOnly)
		float HealthValue;
	UPROPERTY(EditDefaultsOnly, Category = "Currency")
		int32 CreditCost;

	virtual void PawnPickup(APawn* PawnToPickup) override;
	virtual void RespawnPickup() override;

};
