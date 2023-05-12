// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modifiers/CMT_CCTVCameraModifier.h"
#include "Modifiers/CMT_ThirdPersonModifier.h"
#include "Modifiers/CMT_TopDownModifier.h"
#include "CMT_PlayerCameraManager.generated.h"

UENUM(BlueprintType)
enum ECameraMode
{
	TopDown,
	ThirdPerson,
	CCTV,
	Default
};

UCLASS()
class CAMERAMANAGERTEST_API ACMT_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraModifier> TopDownCameraModifier = UCMT_TopDownModifier::StaticClass();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraModifier> ThirdPersonCameraModifier = UCMT_ThirdPersonModifier::StaticClass();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraModifier> CCTVCameraModifier = UCMT_CCTVCameraModifier::StaticClass();
	
protected:
	ECameraMode CameraMode = ECameraMode::TopDown;
	
	ECameraMode PreviousCameraMode = ECameraMode::ThirdPerson;

public:
	ECameraMode GetPreviousCameraMode() const { return PreviousCameraMode; }

	ECameraMode GetCameraMode() const { return CameraMode; }

	void SetCameraMode(ECameraMode newCameraMode);
};
