// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect.h"

#include "SActionComponent.h"

void USActionEffect::ExecutePeriodicEffect_Implementation(AActor* Instigator) {
	// For Overriding in child classes
}

USActionEffect::USActionEffect() {
	bAutoStart = true;

}

void USActionEffect::StartAction_Implementation(AActor* Instigator) {
	Super::StartAction_Implementation(Instigator);

	if (Duration > 0.f) {
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "StopAction", Instigator);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Duration, Delegate, Duration, false);
	}
	if (Period > 0.f) {
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "ExecutePeriodicEffect", Instigator);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Period, Delegate, Period, true);
	}

}

void USActionEffect::StopAction_Implementation(AActor* Instigator) {

	if (GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle_Period) < KINDA_SMALL_NUMBER) {
		ExecutePeriodicEffect(Instigator);
	}

	Super::StopAction_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Period);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Duration);

	USActionComponent* ActionComponent = GetOwningComponent();
	if (ActionComponent) {
		ActionComponent->RemoveAction(this);
	}


}
