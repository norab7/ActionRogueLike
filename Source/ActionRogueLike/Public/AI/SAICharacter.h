// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class ACTIONROGUELIKE_API ASAICharacter : public ACharacter {
	GENERATED_BODY()

public:

	ASAICharacter();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USAttributeComponent* AttributeComponent;

	UFUNCTION()
		void OnPawnSeen(APawn* Pawn);

	void PostInitializeComponents() override;

};
