// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ASAIController::BeginPlay() {
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior tree is nullptr, Please assign BehaviorTree in your AI Controller."))) {
		RunBehaviorTree(BehaviorTree);
	}


	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	//if (PlayerPawn) {
	//	GetBlackboardComponent()->SetValueAsVector("MoveToLocation", PlayerPawn->GetActorLocation());
	//	GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);

	//}

}
