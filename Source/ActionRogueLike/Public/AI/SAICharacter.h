// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USActionComponent;
class USWorldUserWidget;
class UUserWidget;
class USAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter {
	GENERATED_BODY()

public:

	ASAICharacter();

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USAttributeComponent* AttributeComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USActionComponent* ActionComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
		float PrimaryAttackDelay;
	UPROPERTY(EditAnywhere, Category = "Effects")
		FColor HitFlashColor;
	UPROPERTY(EditAnywhere, Category = "Effects")
		float HitFlashSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName HitFlashColorName;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName HitFlashSpeedName;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
		FName TimeToHitName;



	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> HealthBarWidgetClass;

	USWorldUserWidget* ActiveHealthBar;

	UFUNCTION()
		void OnPawnSeen(APawn* Pawn);
	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComponent, float NewHealth, float Delta);

	void SetTargetActor(AActor* TargetActor);

public:
	UPROPERTY(VisibleAnywhere, Category = "Currency")
		int32 CreditValue;

};
