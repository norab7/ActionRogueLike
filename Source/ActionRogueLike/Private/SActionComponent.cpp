// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionComponent.h"

#include "SAction.h"

// Sets default values for this component's properties
USActionComponent::USActionComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USActionComponent::BeginPlay() {
	Super::BeginPlay();

	// ...

	for (TSubclassOf<USAction> ActionClass : DefaultActions) {
		AddAction(GetOwner(), ActionClass);
	}

}


// Called every frame
void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	FString DebugMessage = GetNameSafe(GetOwner()) + ": " + ActiveGameplayTags.ToStringSimple();
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, DebugMessage);

}

void USActionComponent::AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass) {
	if (!ensure(ActionClass)) {
		return;
	}

	USAction* NewAction = NewObject<USAction>(this, ActionClass);
	if (ensure(NewAction)) {
		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator))) {
			NewAction->StartAction(Instigator);
		}
	}
}

bool USActionComponent::RemoveAction(USAction* ActionToRemove) {
	if (ensure(ActionToRemove && !ActionToRemove->GetIsRunning())) {
		if (Actions.Contains(ActionToRemove)) {
			Actions.Remove(ActionToRemove);
			return true;
		}
	}
	return false;
}

bool USActionComponent::StartActionByName(AActor* Instigator, FName ActionName) {
	for (USAction* Action : Actions) {
		if (Action && Action->ActionName == ActionName) {
			if (!Action->CanStart(Instigator)) {
				FString FailedMessage = FString::Printf(TEXT("Failed to run: %s."), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FailedMessage);
				continue;
			}

			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool USActionComponent::StopActionByName(AActor* Instigator, FName ActionName) {
	for (USAction* Action : Actions) {
		if (Action && Action->ActionName == ActionName) {
			if (Action->GetIsRunning()) {
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}

