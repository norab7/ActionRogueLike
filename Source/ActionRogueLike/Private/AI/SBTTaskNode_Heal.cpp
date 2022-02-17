// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTaskNode_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTaskNode_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (ensure(OwnerController)) {

		ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerController->GetPawn());
		if (OwnerCharacter) {

			USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(OwnerCharacter->GetComponentByClass(USAttributeComponent::StaticClass()));
			if (AttributeComponent) {

				AttributeComponent->ApplyHealthChange(OwnerCharacter, bHealToFull ? AttributeComponent->GetMissingHealth() : HealAmount);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
