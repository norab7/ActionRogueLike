// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

class USActionComponent;
class UWorld;

/**
 *
 */
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject {
	GENERATED_BODY()


protected:

	// Properties
	bool bIsRunning;


	// Functions
	UFUNCTION(BlueprintCallable, Category = "Action")
		USActionComponent* GetOwningComponent() const;



	// Tags added to owning actor when activated, removed when action stops.
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer GrantTags;
	// Action an only start if OwningActor has none of these tags applied.
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer BlockedTags;


public:

	/* Action nickname to start/stop without a reference to object */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
		FName ActionName;
	UPROPERTY(EditDefaultsOnly, Category = "Action")
		bool bAutoStart;

	UFUNCTION(BlueprintCallable, Category = "Action")
		bool GetIsRunning() const;
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		bool CanStart(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
		void StartAction(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Action")
		void StopAction(AActor* Instigator);

	virtual UWorld* GetWorld() const override;

};
