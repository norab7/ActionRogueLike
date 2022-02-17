// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

USBTTask_RangedAttack::USBTTask_RangedAttack() {

	MaxBulletSpreadVertical = 2.f;
	MaxBulletSpreadHorizontal = 5.f;
}

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (ensure(OwnerController)) {

		// Owner Null Check
		ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerController->GetPawn());
		if (!OwnerCharacter) {
			return EBTNodeResult::Failed;
		}

		// Target Null Check
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (!TargetActor) {
			return EBTNodeResult::Failed;
		}

		// Is Actor Alive
		if (!USAttributeComponent::IsActorAlive(TargetActor)) {
			return EBTNodeResult::Failed;
		}

		// Locations
		FVector MuzzleLocation = OwnerCharacter->GetMesh()->GetSocketLocation("Muzzle_01");
		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		// Random Accuracy
		MuzzleRotation.Pitch += FMath::RandRange(0.f, MaxBulletSpreadVertical);
		MuzzleRotation.Yaw += FMath::RandRange(-MaxBulletSpreadHorizontal, MaxBulletSpreadHorizontal);

		// Spawning
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = OwnerCharacter;
		AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParameters);


		return SpawnedProjectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;

	}

	return EBTNodeResult::Failed;
}
