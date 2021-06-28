// Copyright of Jorge Luque

#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	// cache references and win/lose conditions.
	// call GameStart_CPP to initialize the start countdown, turret activation, pawn check
	Super::BeginPlay();

	GameStart_CPP();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		GameOver_CPP(false);
	}

	// Assigns the value of the Cast to DestroyedTurret and then evaluates the value of DestroyedTurret.
	// Cast returns null if the cast isn't successful.
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		// Decrement EnemyTurretCounts first and then check if there are no more enemies left.
		if (--EnemyTurretsCount == 0)
		{
			GameOver_CPP(true);
		}
	}
}

int32 ATankGameModeBase::GetEnemyTurretsCount()
{
	TArray<AActor*> EnemyTurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), EnemyTurretActors);
	return EnemyTurretActors.Num();
}

void ATankGameModeBase::GameStart_CPP()
{
	// initialize the start countdown, turret activation, pawn check
	EnemyTurretsCount = GetEnemyTurretsCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GameStart_BP();
}

void ATankGameModeBase::GameOver_CPP(bool PlayerWon)
{
	// show win screen if player destroyed all the turrets
	// if player got killed, show lose screen.
	// Call GameOver_BP
	GameOver_BP(PlayerWon);
}
