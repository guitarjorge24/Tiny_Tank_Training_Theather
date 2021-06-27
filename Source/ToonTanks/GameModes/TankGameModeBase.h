// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart_BP();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver_BP(bool PlayerWon);

private:
	// #ToDoJ: rename these "handle" functions to something more descriptive
	void GameStart_CPP();
	void GameOver_CPP(bool PlayerWon);
};
