// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"


class USAction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API USActionComponent : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USActionComponent();

protected:

	UPROPERTY(EditAnywhere, Category = "Actions")
		TArray<TSubclassOf<USAction>> DefaultActions;
	UPROPERTY()
		TArray<USAction*> Actions;

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FGameplayTagContainer ActiveGameplayTags;



	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass);
	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool RemoveAction(USAction* ActionToRemove);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool StartActionByName(AActor* Instigator, FName ActionName);
	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool StopActionByName(AActor* Instigator, FName ActionName);


};
