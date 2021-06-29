// Copyright of Jorge Luque


#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnTank::APawnTank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent); // Attaching to Capsule Component
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();

	if(PlayerController)
	{
		FHitResult TraceHitResult;
		// GetHitResultUnderCursor makes a line trace starting from the current camera location and creates a
		// normalized direction based on the cursor position which is multiplied by
		// APlayerController::HitResultTraceDistance to determine the end location of the line trace.
		// This works for a top down shooter but in my case I have the camera slightly 3rd-person-ish which allows
		// the player to look forward and point the mouse to the horizon which means the line trace doesn't hit anything.
		// We use the Visibility collision channel so that the line trace hits anything that's visible.
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;

		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

bool APawnTank::GetIsPlayerAlive() const
{
	return bIsPlayerAlive;
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false); // stops movement and rotation logic that gets run on Tick()
}

void APawnTank::CalculateMoveInput(float Value)
{
	TranslationAmountPerFrame = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmountPerFrame = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmountPerFrame, 0);
	RotateAmountPerFrameinQuat = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(TranslationAmountPerFrame, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotateAmountPerFrameinQuat, true);
}
