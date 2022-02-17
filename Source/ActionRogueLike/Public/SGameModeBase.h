// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class ASPickupBase;
class UEnvQueryInstanceBlueprintWrapper;
class UEnvQuery;
/**
 *
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase {
	GENERATED_BODY()

public:
	ASGameModeBase();
	virtual void StartPlay() override;
protected:


	// Spawn Items
	FTimerHandle TimerHandle_SpawnItems;
	UPROPERTY(EditDefaultsOnly, Category = "Items")
		UEnvQuery* SpawnItemsQuery;
	UPROPERTY(EditDefaultsOnly, Category = "Items")
		TArray<TSubclassOf<AActor>> SpawnableItems;
	UPROPERTY(EditDefaultsOnly, Category = "Items")
		float SpawnItemInterval;
	UFUNCTION()
		void SpawnItemTimeElapsed();
	UFUNCTION()
		void OnItemSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	// Spawn Bots
	FTimerHandle TimerHandle_SpawnBots;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UEnvQuery* SpawnBotQuery;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		TSubclassOf<AActor> MinionClass;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UCurveFloat* DifficultyCurve;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SpawnTimerInterval;
	UFUNCTION()
		void SpawnBotTimeElapsed();
	UFUNCTION()
		void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

public:

	UFUNCTION(Exec)
		void KillAllBots();
	UFUNCTION(Exec)
		void KillAllPlayers();

	UFUNCTION()
		virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);
	UFUNCTION()
		void RespawnPlayerElapsed(AController* Controller);

};
