// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"

#include "PawnTank.generated.h"

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

public:
	APawnTank();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetIsPlayerAlive() const;
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	UPROPERTY()
	APlayerController* PlayerController;

	bool bIsPlayerAlive = true;
	
	/** @brief How many units to move forward/backward in 1 second with a fully activated input axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank Movement", meta=(AllowPrivateAccess = "true"))
	float MoveSpeed = 100.f;
	/** @brief How many degrees to rotate clockwise/anti-clockwise in 1 second with a fully activated "Turn" input axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank Movement", meta=(AllowPrivateAccess = "true"))
	float RotateSpeed = 100.f;
	/** @brief How much to move the tank forward/backwards on a single game frame */
	FVector TranslationAmountPerFrame;
	/** @brief How much to rotate tank by in quaternions on a single game frame (when pressing A or D) */
	FQuat RotateAmountPerFrameinQuat;


	
	/**
	* @brief Calculate the value of TranslationAmountPerFrame
	* @param Value Input Axis Value
	*/
	void CalculateMoveInput(float Value);
	/**
 	* @brief Calculate value of RotateAmountPerFrameinQuat
 	* @param Value Input Axis Value
 	*/
	void CalculateRotateInput(float Value);
	/** @brief Called in Tick. Calls AddActorLocalOffset to add change in actor location along it's local axis.	*/
	void Move();
	/** @brief Called in Tick. Calls AddActorLocalRotation to add change in actor local rotation axes. */
	void Rotate();
};
