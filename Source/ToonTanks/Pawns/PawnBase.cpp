// Copyright of Jorge Luque

#include "PawnBase.h"

#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

APawnBase::APawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(FVector LocationToLookAt)
{
	FVector LookAtTargetCleaned = FVector(
		LocationToLookAt.X, LocationToLookAt.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	// Get ProjectileSpawnPoint's Location & Rotation
	// Then spawn Projectile class at Location firing towards Rotation
	// #ToDoJ: The rotation we need is probably not the local rotation since that one will be 0 since the
	// ProjectileSpawnPoint is attached to the TurretMesh. We need the world rotation.

	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(
			ProjectileClass, SpawnLocation, SpawnRotation);

		TempProjectile->SetOwner(this);
		TempProjectile->ProjectileMesh->IgnoreActorWhenMoving(this, true);
	}

	UE_LOG(LogTemp, Warning, TEXT("Fire Condition Success"))
}

void APawnBase::HandleDestruction()
{
	// == Universal Functionality (stuff to call using Super::) ==
	// Play death effects particle, sound, and camera shake.
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathShake); // diff method of getting PlayerController w/o using UGameplayStatics::GetPlayerController()
	
	// == Child-specific functionality ==
	// - PawnTurret: Inform GameMode that the Turret died. Then Destroy() self.
	// - PawnTank: Inform GameMode that the Player died. Then Hide() all components and stop movement input.
	//   We don't want to destroy the Player not only because it more performance intensive to destroy and respawn it
	//   but also because it destroys the player camera and it ends up jumping to the default camera which looks bad.

	// #ToDoJ: The GameMode will be tracking how many turrets there are when a turret pawn is destroyed,
	// This could also be tracked on the GameState.
}
