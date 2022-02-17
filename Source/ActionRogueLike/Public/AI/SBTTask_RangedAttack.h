// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_RangedAttack.generated.h"

class ASProjectileBase;
/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API USBTTask_RangedAttack : public UBTTaskNode {
	GENERATED_BODY()

public:
	USBTTask_RangedAttack();

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<AActor> ProjectileClass;

	// Bullet Spread
	UPROPERTY(EditAnywhere, Category = "AI")
		float MaxBulletSpreadVertical;
	UPROPERTY(EditAnywhere, Category = "AI")
		float MaxBulletSpreadHorizontal;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
