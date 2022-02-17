// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckLowHealth.generated.h"

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API USBTService_CheckLowHealth : public UBTService {
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
		float LowHealthValue = 50.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		FBlackboardKeySelector LowHealthBoolKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
