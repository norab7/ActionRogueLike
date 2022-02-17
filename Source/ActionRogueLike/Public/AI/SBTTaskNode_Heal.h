// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTaskNode_Heal.generated.h"

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API USBTTaskNode_Heal : public UBTTaskNode {
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, Category = "AI")
		float HealAmount = 20.f;
	UPROPERTY(EditAnywhere, Category = "AI")
		bool bHealToFull = false;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
