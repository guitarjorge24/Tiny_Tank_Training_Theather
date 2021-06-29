// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	/**
 	* @brief Enables or disables receiving player input on the PlayerController. Used to disable input before the
 	* countdown timer has finished and when the player has died. 
 	* @param SetPlayerEnabled true if the input should be enabled
 	*/
	void SetPlayerEnabledState(bool SetPlayerEnabled);
};
