// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	BarrelMesh->SetSimulatePhysics(true);
	BarrelMesh->SetCollisionProfileName("PhysicsActor");
	BarrelMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnBarrelHit);

	RootComponent = BarrelMesh;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(BarrelMesh);
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->Radius = 1000.f;
	RadialForceComponent->ForceStrength = 1000.f;

}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrel::OnBarrelHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	RadialForceComponent->FireImpulse();
}