// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraManagerTestGameMode.h"
#include "CameraManagerTestCharacter.h"
#include "CMT_PlayerController.h"
#include "UObject/ConstructorHelpers.h"

ACameraManagerTestGameMode::ACameraManagerTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = ACMT_PlayerController::StaticClass();
	}
}
