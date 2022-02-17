// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "DrawDebugHelpers.h"
#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "SWorldUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

static TAutoConsoleVariable<bool> CVarPlayerSightingDebug(TEXT("sl.PlayerSightingDebug"), false, TEXT("Enable debug print string of enemies sighting players."));

// Sets default values
ASAICharacter::ASAICharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");
	ActionComponent = CreateDefaultSubobject<USActionComponent>("ActionComponent");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HitFlashColor = FColor::White;
	HitFlashSpeed = 2.f;

	HitFlashColorName = "HitFlashColor";
	HitFlashSpeedName = "HitFlashSpeed";
	TimeToHitName = "TimeToHit";

	CreditValue = 3;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

}

void ASAICharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);

}

void ASAICharacter::OnPawnSeen(APawn* Pawn) {
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController) {
		SetTargetActor(Pawn);

		if (CVarPlayerSightingDebug.GetValueOnGameThread()) {
			DrawDebugString(GetWorld(), Pawn->GetActorLocation(), TEXT("Player Spotted"), nullptr, FColor::Red, 4.0f, true);
		}
	}
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta) {
	if (Delta < 0.f) {

		if (InstigatorActor && InstigatorActor != this) {
			SetTargetActor(InstigatorActor);
		}


		if (!ActiveHealthBar) {
			if (NewHealth > 0.f) {
				ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
				if (ActiveHealthBar) {
					ActiveHealthBar->AttachedActor = this;
					ActiveHealthBar->AddToViewport();
				}
			}
		}

		FVector NormalColor = FVector(HitFlashColor.R, HitFlashColor.G, HitFlashColor.B);
		NormalColor.Normalize();
		GetMesh()->SetVectorParameterValueOnMaterials(HitFlashColorName, NormalColor);
		GetMesh()->SetScalarParameterValueOnMaterials(HitFlashSpeedName, HitFlashSpeed);
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitName, GetWorld()->TimeSeconds);


		// On Death
		if (NewHealth <= 0.f) {
			// Stop BT
			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController) {
				AIController->GetBrainComponent()->StopLogic("Killed");
			}

			// Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			// Set LifeSpan
			SetLifeSpan(10.f);
		}
	}

}

void ASAICharacter::SetTargetActor(AActor* TargetActor) {

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController) {
		AIController->GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetActor);
	}
}

