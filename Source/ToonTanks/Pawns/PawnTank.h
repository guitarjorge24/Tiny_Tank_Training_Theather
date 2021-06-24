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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void HandleDestruction() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank Movement", meta=(AllowPrivateAccess = "true"))
	float MoveSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tank Movement", meta=(AllowPrivateAccess = "true"))
	float RotateSpeed = 100.f;

	APlayerController* PlayerController;
	
	FVector TranslationAmountPerFrame;
	FQuat RotationDirection;

	/**
	* @brief 
	* @param Value Input Axis Value
	*/
	void CalculateMoveInput(float Value);
	/**
 	* @brief 
 	* @param Value Input Axis Value
 	*/
	void CalculateRotateInput(float Value);

	/**
	* @brief Adds a change in the location of an actor along it's local axis.  
	*/
	void Move();
	void Rotate();
};
