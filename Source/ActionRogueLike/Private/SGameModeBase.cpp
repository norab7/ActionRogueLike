// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SPickupBase.h"
#include "SPlayerState.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"


static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("sl.SpawnBots"), true, TEXT("Enable spawning of bots via Timer."), ECVF_Cheat);
static TAutoConsoleVariable<bool> CVarSpawnItems(TEXT("sl.SpawnItems"), true, TEXT("Enable spawning of items via Timer."), ECVF_Cheat);


ASGameModeBase::ASGameModeBase() {

	SpawnTimerInterval = 2.f;
	SpawnItemInterval = 5.f;
}


void ASGameModeBase::StartPlay() {
	Super::StartPlay();

	// Set Timers
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBotTimeElapsed, SpawnTimerInterval, true);
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnItems, this, &ASGameModeBase::SpawnItemTimeElapsed, SpawnItemInterval, true);
}


void ASGameModeBase::SpawnItemTimeElapsed() {
	if (!CVarSpawnItems.GetValueOnGameThread()) {
		UE_LOG(LogTemp, Warning, TEXT("Item spawning disabled via cvar CVarSpawnItems."));
		return;
	}

	int32 SpawnedPickups = 0;
	for (TActorIterator<ASPickupBase> It(GetWorld()); It; ++It) {
		SpawnedPickups++;
	}
	int32 MaxItemsCount = 30;
	if (SpawnedPickups >= MaxItemsCount) {
		UE_LOG(LogTemp, Log, TEXT("Maximum(%i) Items spawned."), MaxItemsCount);
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnItemsQuery, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);

	if (ensure(QueryInstance)) {
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnItemSpawnQueryCompleted);
	}

}

void ASGameModeBase::OnItemSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus) {

	if (QueryStatus != EEnvQueryStatus::Success) {
		UE_LOG(LogTemp, Warning, TEXT("Spawn Item EQS Query failed"));
		return;
	}


	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (!Locations.IsEmpty()) {
		if (!SpawnableItems.IsEmpty()) {

			GetWorld()->SpawnActor<AActor>(SpawnableItems[FMath::RandRange(0, SpawnableItems.Num() - 1)], Locations[0] + FVector(0.f, 0.f, 50.f), FRotator::ZeroRotator);

		}
	}

}

void ASGameModeBase::SpawnBotTimeElapsed() {

	if (!CVarSpawnBots.GetValueOnGameThread()) {
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar CVarSpawnBots."));
		return;
	}

	int32 AliveBotsCount = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It) {
		ASAICharacter* Bot = *It;

		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComponent)) {
			if (AttributeComponent->IsAlive()) {
				AliveBotsCount++;
			}
		} else {
			AliveBotsCount++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots"), AliveBotsCount);

	float MaxBotCount = 10.f;
	if (DifficultyCurve) {
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}


	if (AliveBotsCount >= MaxBotCount) {
		UE_LOG(LogTemp, Log, TEXT("Maximum(%i) number of bots spawned"), MaxBotCount);
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance)) {
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus) {

	if (QueryStatus != EEnvQueryStatus::Success) {
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query failed"));
		return;
	}


	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (!Locations.IsEmpty()) {
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

	}
}


void ASGameModeBase::KillAllBots() {

	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It) {
		ASAICharacter* Bot = *It;

		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComponent)) {
			if (AttributeComponent->IsAlive()) {
				AttributeComponent->Kill(this);
			}
		}
	}

}

void ASGameModeBase::KillAllPlayers() {
	for (TActorIterator<ASCharacter> It(GetWorld()); It; ++It) {
		ASCharacter* Player = *It;

		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributes(Player);
		if (ensure(AttributeComponent)) {
			if (AttributeComponent->IsAlive()) {
				AttributeComponent->Kill(this);
			}
		}
	}

}

void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer) {

	if (ASCharacter* PlayerVictim = Cast<ASCharacter>(VictimActor)) {
		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", PlayerVictim->GetController());

		float RespawnDelay = 2.f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}

	if (APawn* KillerPawn = Cast<APawn>(Killer)) {
		if (ASPlayerState* PlayerState = KillerPawn->GetPlayerState<ASPlayerState>()) {
			if (ASAICharacter* VictimBot = Cast<ASAICharacter>(VictimActor)) {
				PlayerState->AddCredits(VictimBot->CreditValue);
			}
		}
	}


	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));

}

void ASGameModeBase::RespawnPlayerElapsed(AController* Controller) {

	if (Controller) {
		Controller->UnPossess();
		RestartPlayer(Controller);
	}

}

