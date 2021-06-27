// Copyright of Jorge Luque

#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	// cache references and win/lose conditions.
	// call GameStart_CPP to initialize the start countdown, turret activation, pawn check
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// if player died then end game with lose condition.
	// if enemy turret died, add to the score
}

void ATankGameModeBase::GameStart_CPP()
{
	// initialize the start countdown, turret activation, pawn check
}

void ATankGameModeBase::GameOver_CPP(bool PlayerWon)
{
	// show win screen if player destroyed all the turrets
	// if player got killed, show lose screen.
	// Call GameOver_BP
}
