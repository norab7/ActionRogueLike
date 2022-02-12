// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between Pawn and Target Actor

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent)) {

		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if (TargetActor) {

			AAIController* OwnerController = OwnerComp.GetAIOwner();
			if (ensure(OwnerController)) {

				APawn* OwnerPawn = OwnerController->GetPawn();
				if (ensure(OwnerPawn)) {
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), OwnerPawn->GetActorLocation());
					bool bWithinRange = DistanceTo < 2000.f;

					bool bHasLineOfSight = false;
					if (bWithinRange) {
						bHasLineOfSight = OwnerController->LineOfSightTo(TargetActor);
					}

					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLineOfSight);

				}
			}
		}
	}

}
