// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SActionEffect.generated.h"

/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API USActionEffect : public USAction {
	GENERATED_BODY()

public:
	USActionEffect();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		float Duration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
		float Period;

	FTimerHandle TimerHandle_Duration;
	FTimerHandle TimerHandle_Period;

	UFUNCTION(BlueprintNativeEvent, Category = "Effect")
		void ExecutePeriodicEffect(AActor* Instigator);

public:
	void StartAction_Implementation(AActor* Instigator) override;
	void StopAction_Implementation(AActor* Instigator) override;

};
