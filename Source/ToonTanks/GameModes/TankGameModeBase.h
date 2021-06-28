// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "TankGameModeBase.generated.h"

/**
 * @brief Handles the events when an actor dies and when the game starts or is over.
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/**
	* @brief If player died then end game with lose condition.If enemy turret died, add to the score.
 	* @param DeadActor The actor who just died.
 	* @return 
 	*/
	void ActorDied(AActor* DeadActor);

protected:
	/**
	* @brief The pre-game countdown. Should be set to 1 more second than the number you want the
	* countdown to start so that  "GO!" counts as one last second.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Game Loop")
	int32 StartDelay = 3;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart_BP();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver_BP(bool PlayerWon);

private:
	class APawnTank* PlayerTank;
	/**
	* @brief The number of remaining enemy turrets in the level. 
	*/
	int32 EnemyTurretsCount = 0;
	int32 GetEnemyTurretsCount();

	// #ToDoJ: rename these GAmeStart/Over functions to something more descriptive or add docs so that it is clear
	// how the _CPP ones are different from the BP ones which set widget related stuff.
	void GameStart_CPP();
	void GameOver_CPP(bool PlayerWon);
};
