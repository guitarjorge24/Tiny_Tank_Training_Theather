// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	/**
 	* @brief  Bound to the OnTakeAnyDamage delegate which gets bound to this component'sowner (the pawn).
 	* When the projectile hits something, it calls UGameplayStatics::ApplyDamage which triggers this delegate.
 	*/
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		AController* InstigatedBy, AActor* DamageCauser);

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;
	float CurrentHealth = 0.f;

	class ATankGameModeBase* GameModeRef;
};
