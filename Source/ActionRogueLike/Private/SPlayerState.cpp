// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

float ASPlayerState::GetCredits() {
	return Credits;
}

void ASPlayerState::SetCredits(int32 Delta) {
	if (!ensure(Delta > 0.f)) {
		return;
	}
	Credits = Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

void ASPlayerState::AddCredits(int32 Delta) {
	if (!ensure(Delta > 0.f)) {
		return;
	}
	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);

}

bool ASPlayerState::RemoveCredits(int32 Delta) {
	if (!ensure(Delta > 0.f)) {
		return false;
	}
	if (Credits < Delta) {
		return false;
	}

	Credits -= Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);

	return true;
}
