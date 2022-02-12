// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (ensure(OwnerController)) {

		ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerController->GetPawn());
		if (!OwnerCharacter) {
			return EBTNodeResult::Failed;
		}

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (!TargetActor) {
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = OwnerCharacter->GetMesh()->GetSocketLocation("Muzzle_01");
		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = OwnerCharacter;

		AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParameters);

		return SpawnedProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;

	}

	return EBTNodeResult::Failed;
}
