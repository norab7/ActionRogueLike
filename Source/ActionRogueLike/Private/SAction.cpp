// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"

#include "SActionComponent.h"


USActionComponent* USAction::GetOwningComponent() const {
	return Cast<USActionComponent>(GetOuter());
}

void USAction::StartAction_Implementation(AActor* Instigator) {
	UE_LOG(LogTemp, Log, TEXT("Running Action: %s."), *GetNameSafe(this));

	USActionComponent* ActionComponent = GetOwningComponent();
	ActionComponent->ActiveGameplayTags.AppendTags(GrantTags);

	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* Instigator) {
	UE_LOG(LogTemp, Log, TEXT("Stopping Action: %s."), *GetNameSafe(this));

	ensureAlways(bIsRunning);

	USActionComponent* ActionComponent = GetOwningComponent();
	ActionComponent->ActiveGameplayTags.RemoveTags(GrantTags);

	bIsRunning = false;
}

bool USAction::GetIsRunning() const {
	return bIsRunning;
}

bool USAction::CanStart_Implementation(AActor* Instigator) {

	if (bIsRunning) {
		return false;
	}

	USActionComponent* ActionComponent = GetOwningComponent();
	if (ActionComponent->ActiveGameplayTags.HasAny(BlockedTags)) {
		return false;
	}
	return true;
}

UWorld* USAction::GetWorld() const {

	// Outer is set when creating action via NewObject<T>
	UActorComponent* Component = Cast<UActorComponent>(GetOuter());
	if (Component) {
		return Component->GetWorld();
	}
	return nullptr;
}
