// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"

#include "MatineeCameraShake.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASProjectileBase::ASProjectileBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpeed = 8000.f;
	bExplodeOnHit = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionProfileName("Projectile");

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>("EffectComponent");
	EffectComponent->SetupAttachment(SphereComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("TravelSoundComponent");
	AudioComponent->SetupAttachment(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	SphereComponent->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);

}

// Called when the game starts or when spawned
void ASProjectileBase::BeginPlay() {
	Super::BeginPlay();

	UGameplayStatics::SpawnEmitterAtLocation(this, SpawnEffect, GetActorLocation(), GetActorRotation());

}

void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (bExplodeOnHit) {
		Explode();
	}
}

void ASProjectileBase::Explode_Implementation() {
	if (ensure(!IsPendingKill())) {
		ExplodeEffects();
		Destroy();
	}
}

void ASProjectileBase::ExplodeEffects() {
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), 500.f, 1000.f);
	EffectComponent->Deactivate();
	ProjectileMovementComponent->StopMovementImmediately();
	SetActorEnableCollision(false);
}

// Called every frame
void ASProjectileBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ASProjectileBase::PostInitializeComponents() {
	Super::PostInitializeComponents();
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

