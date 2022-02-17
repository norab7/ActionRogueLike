// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent)) {

		AAIController* OwnerController = OwnerComp.GetAIOwner();
		if (ensure(OwnerController)) {

			ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerController->GetPawn());
			if (OwnerCharacter) {

				USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(OwnerCharacter->GetComponentByClass(USAttributeComponent::StaticClass()));
				if (AttributeComponent) {

					bool bHealthLow = AttributeComponent->GetHealth() < LowHealthValue;
					BlackboardComponent->SetValueAsBool(LowHealthBoolKey.SelectedKeyName, bHealthLow);

				}
			}
		}
	}
}
