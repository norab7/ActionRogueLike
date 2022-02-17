// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickupBase.h"

#include "Components/SphereComponent.h"

static TAutoConsoleVariable<bool> CVarAllowPickupOverlaps(TEXT("sl.PlayerPickupOnOverlap"), true, TEXT("Allows the player to collect pickups on overlapping them."));


// Sets default values
ASPickupBase::ASPickupBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Properties
	SphereRadius = 50.f;
	RespawnDelay = 10.f;


	// Components
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = BaseMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(BaseMesh);
	SphereComponent->SetSphereRadius(SphereRadius, false);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}


void ASPickupBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (CVarAllowPickupOverlaps.GetValueOnGameThread() && OtherActor) {
		if (APawn* OtherPawn = Cast<APawn>(OtherActor)) {
			PawnPickup(OtherPawn);
		}
	}
}

void ASPickupBase::PawnPickup(APawn* PawnToPickup) {
	SetPickupActiveState(false);
}

void ASPickupBase::RespawnPickup() {
	SetPickupActiveState(true);
}

void ASPickupBase::SetPickupActiveState(bool bSetPickupActive) {
	RootComponent->SetVisibility(bSetPickupActive, true);
	SetActorEnableCollision(bSetPickupActive);
}

void ASPickupBase::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASPickupBase::OnSphereOverlap);
}

void ASPickupBase::Interact_Implementation(APawn* InstigatorPawn) {
	if (InstigatorPawn) {
		PawnPickup(InstigatorPawn);
	}
}

