// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CMT_PlayerCameraManager.h"
#include "CMT_PlayerController.generated.h"

class UCameraModifier;
class UInputAction;

/**
 * 
 */
UCLASS()
class CAMERAMANAGERTEST_API ACMT_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchCameraModeInputAction;

protected:
	TWeakObjectPtr<ACMT_PlayerCameraManager> CMTPlayerCameraManager; 
	
public:
	ACMT_PlayerController(const FObjectInitializer& ObjectInitializer);

	void SwapCameraMode();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

	virtual void SpawnPlayerCameraManager() override;

	UFUNCTION(BlueprintCallable)
	virtual void ToggleCCTVTargetWithBlend(AActor* NewViewTarget, FRotator NewControlRotation, float BlendTime, EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing);
	
	ECameraMode GetCameraMode();
};
