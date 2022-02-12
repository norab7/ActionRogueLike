// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Properties
	ForceRadius = 1000.f;
	ForceStrength = 1000.f;

	// Setup Barrel Mesh
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	BarrelMesh->SetSimulatePhysics(true);
	BarrelMesh->SetCollisionProfileName("PhysicsActor");

	// Replace RootComponent
	RootComponent = BarrelMesh;

	// Setup RadialForceComponent
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(BarrelMesh);
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->Radius = ForceRadius;
	RadialForceComponent->ForceStrength = ForceStrength;
	RadialForceComponent->SetAutoActivate(false);
	RadialForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay() {
	Super::BeginPlay();

}

void ASExplosiveBarrel::PostInitializeComponents() {
	Super::PostInitializeComponents();

	// Bind Events
	BarrelMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnBarrelHit);
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrel::OnBarrelHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	RadialForceComponent->FireImpulse();

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(this), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location %s"), *Hit.ImpactPoint.ToString());

	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.f, true);

}