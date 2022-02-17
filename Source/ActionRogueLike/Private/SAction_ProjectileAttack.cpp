// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USAction_ProjectileAttack::USAction_ProjectileAttack() {
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter) {

	if (ensure(ProjectileClass)) {

		// Spawn Parameters
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Instigator = InstigatorCharacter;

		// Collision Shape
		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		// Collision Query Params
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(InstigatorCharacter);

		// Collision Object Params
		FCollisionObjectQueryParams CollisionObjectParams;
		CollisionObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		CollisionObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
		CollisionObjectParams.AddObjectTypesToQuery(ECC_Pawn);

		// Trace Start/End
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();
		FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000.f);

		// Hit Results
		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, CollisionObjectParams, Shape, CollisionQueryParams)) {
			TraceEnd = Hit.ImpactPoint;
		}

		// Spawn Transform
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
		FRotator ProjectileRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		FTransform SpawnTransform = FTransform(ProjectileRotation, HandLocation);

		// Spawn Actor
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParameters);

	}

	// Stop because no longer shooting projectile
	StopAction(InstigatorCharacter);

}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator) {
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character) {
		Character->PlayAnimMontage(AttackAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "AttackDelay_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay, Delegate, AttackAnimDelay, false);

	}
}

void USAction_ProjectileAttack::StopAction_Implementation(AActor* Instigator) {
	Super::StopAction_Implementation(Instigator);



}
