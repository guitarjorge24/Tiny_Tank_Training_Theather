// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
// It's good practice to include every .h your cpp needs, even if StaticMeshComponent is included by something else
#include "Components/StaticMeshComponent.h"  
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->InitialSpeed = MovementSpeed;
	ProjectileMovementComponent->MaxSpeed = MovementSpeed;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);
	
	InitialLifeSpan = 3.f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileOwner = GetOwner(); // The pawn that spawned the projectile. Set in APawnBase::Fire().
	if (!ProjectileOwner) { return; }

	// "OtherActor != this" in case there's components of the projectile that could overlap with itself.
	// Check that OtherActor is not the owner to avoid applying damage to the pawn that spawned the projectile.
	if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileOwner->GetInstigatorController(),
			this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		Destroy(); // only destroy if it hits something that isn't the owner or itself.
	}

}
