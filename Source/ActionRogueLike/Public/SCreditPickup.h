// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickupBase.h"
#include "SCreditPickup.generated.h"

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API ASCreditPickup : public ASPickupBase {
	GENERATED_BODY()

public:
	ASCreditPickup();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Currency")
		int32 CreditReward;

	virtual void PawnPickup(APawn* PawnToPickup) override;

};
