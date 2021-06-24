// Copyright of Jorge Luque

#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	// WorldContextObject is something that derives from UObject from which a reference to the world can be obtained
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::CheckFireCondition()
{
	// If player is null or dead, then return
	if (!PlayerPawn) { return; }

	// Ff player is in range, then fire
	if(ReturnDistanceToPlayer() <= FireRange)
	{
		//Fire
		UE_LOG(LogTemp, Warning, TEXT("Fire Condition Success"))
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn) { return 0.f; }
	
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}