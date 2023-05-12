// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraManagerTestCharacter.h"

#include "CMT_PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// ACameraManagerTestCharacter

ACameraManagerTestCharacter::ACameraManagerTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ACameraManagerTestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(CMTPlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACameraManagerTestCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	CMTPlayerController = Cast<ACMT_PlayerController> (Controller);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACameraManagerTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACameraManagerTestCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACameraManagerTestCharacter::Look);

	}

}

void ACameraManagerTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D movementVector = Value.Get<FVector2D>();

	if (CMTPlayerController.IsValid())
	{
		if (CMTPlayerController.Get()->GetCameraMode() == ThirdPerson)
		{
			MoveThirdPerson(movementVector);
			return;
		}

		if (CMTPlayerController.Get()->GetCameraMode() == TopDown)
		{
			MoveTopDown(movementVector);
			return;
		}
	}

	// Todo Make sure to maintain the control rotation when we change the camera point of view until we release the moving input. 
	MoveTopDown(movementVector);
}

void ACameraManagerTestCharacter::MoveTopDown(const FVector2D& movementVector)
{
	if (Controller != nullptr)
	{
		// add movement, Todo replace unit vectors with an arbitrary direction once it's changed per map
		AddMovementInput(FVector::UnitX(), movementVector.Y);
		AddMovementInput(FVector::UnitY(), movementVector.X);
	}
}

void ACameraManagerTestCharacter::MoveThirdPerson(const FVector2D& movementVector)
{
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, movementVector.Y);
		AddMovementInput(RightDirection, movementVector.X);
	}
}

void ACameraManagerTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




