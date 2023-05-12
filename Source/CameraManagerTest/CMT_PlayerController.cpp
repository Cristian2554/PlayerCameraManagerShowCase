// Fill out your copyright notice in the Description page of Project Settings.

#include "CMT_PlayerController.h"
#include "CMT_PlayerCameraManager.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACMT_PlayerController::ACMT_PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ACMT_PlayerCameraManager::StaticClass();
}

void ACMT_PlayerController::SwapCameraMode()
{
	if (CMTPlayerCameraManager.IsValid())
	{
		if(CMTPlayerCameraManager->GetCameraMode() != CCTV)
		{
			// Done this way so it's open to multiple Camera Modes
			CMTPlayerCameraManager.Get()->SetCameraMode(CMTPlayerCameraManager.Get()->GetCameraMode() == TopDown ? ThirdPerson : TopDown);
		}
	}
}

void ACMT_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (CMTPlayerCameraManager.IsValid())
	{
		CMTPlayerCameraManager.Get()->SetCameraMode(TopDown);
	}
}

void ACMT_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhancedInputComponent->BindAction(SwitchCameraModeInputAction, ETriggerEvent::Triggered, this, &ACMT_PlayerController::SwapCameraMode);
	}
}

void ACMT_PlayerController::SpawnPlayerCameraManager()
{
	Super::SpawnPlayerCameraManager();

	CMTPlayerCameraManager = Cast <ACMT_PlayerCameraManager>(PlayerCameraManager);
}

void ACMT_PlayerController::OnCameraModeChanged(const ECameraMode newCameraMode, const ECameraMode previousCameraMode)
{
	OnCameraModeChangedDelegate.Broadcast(newCameraMode, previousCameraMode);
}

void ACMT_PlayerController::ToggleCCTVTargetWithBlend(AActor* NewViewTarget, FRotator NewControlRotation,
                                                      float BlendTime, EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing)
{
	if (CMTPlayerCameraManager.IsValid())
	{
		const ECameraMode previousCameraMode = GetCameraMode();
		if (previousCameraMode == CCTV && NewViewTarget == GetPawn())
		{
			// Go back to the previous Camera Mode
			CMTPlayerCameraManager.Get()->SetCameraMode(CMTPlayerCameraManager.Get()->GetPreviousCameraMode());
			SetViewTargetWithBlend(NewViewTarget, BlendTime, BlendFunc, BlendExp, bLockOutgoing);
		}
		else
		{
			CMTPlayerCameraManager.Get()->SetCameraMode(CCTV);
			SetControlRotation(NewControlRotation);
			SetViewTargetWithBlend(NewViewTarget, BlendTime, BlendFunc, BlendExp, bLockOutgoing);
		}

		OnCameraModeChanged(GetCameraMode(), previousCameraMode);
	}
}

ECameraMode ACMT_PlayerController::GetCameraMode()
{
	if (CMTPlayerCameraManager.IsValid())
	{
		return CMTPlayerCameraManager.Get()->GetCameraMode();
	}

	return Default;
}
