// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectileBase.generated.h"

class UMatineeCameraShake;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS(ABSTRACT)
class ACTIONROGUELIKE_API ASProjectileBase : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UProjectileMovementComponent* ProjectileMovementComponent;

	// Effects
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UParticleSystemComponent* EffectComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		UParticleSystem* ImpactEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		UParticleSystem* SpawnEffect;

	// Audio
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		UAudioComponent* AudioComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		USoundBase* ImpactSound;

	// Shake
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		TSubclassOf<UMatineeCameraShake> ImpactShake;

	// Properties
	UPROPERTY(EditAnywhere)
		float ProjectileSpeed;
	UPROPERTY(EditAnywhere)
		bool bExplodeOnHit;

	// Functions
	UFUNCTION()
		virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Explode();
	virtual void Explode_Implementation();
	UFUNCTION()
		void ExplodeEffects();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

};
