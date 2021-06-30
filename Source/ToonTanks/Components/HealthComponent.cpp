// Copyright of Jorge Luque

#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// Variables that get their values from BP Defaults details panel should not be used in the constructor. By the time
	// the constructor runs, MaxHealth is initialized to the default value from the .h file since the value from the
	// BP Defaults details panel hasn't been applied yet. That's why we set CurrentHealth in BeginPlay instead.
	CurrentHealth = MaxHealth; 
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                  AController* InstigatedBy, AActor* DamageCauser)
{
	// stop tying to subtract health from an actor that is already at zero health.
	if (Damage == 0 || CurrentHealth <= 0) { return; }

	UE_LOG(LogTemp, Warning, TEXT("Health Before: %f"), CurrentHealth)
	// Clamp to make sure health is not less than 0 or greater than max health
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health After: %f"), CurrentHealth)

	if (CurrentHealth <= 0)
	{
		if (GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Reference to GameMode is null in Health Component"));
		}
	}
}
