// Fill out your copyright notice in the Description page of Project Settings.


#include "SCreditPickup.h"

#include "SCharacter.h"
#include "SPlayerState.h"

ASCreditPickup::ASCreditPickup() {
	CreditReward = 5;
}

void ASCreditPickup::PawnPickup(APawn* PawnToPickup) {

	if (ASPlayerState* PlayerState = PawnToPickup->GetPlayerState<ASPlayerState>()) {
		PlayerState->AddCredits(CreditReward);
		Super::PawnPickup(PawnToPickup);
	}
}
