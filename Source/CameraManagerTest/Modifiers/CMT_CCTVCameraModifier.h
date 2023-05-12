// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "CMT_CCTVCameraModifier.generated.h"

/**
 * 
 */
UCLASS()
class CAMERAMANAGERTEST_API UCMT_CCTVCameraModifier : public UCameraModifier
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPostProcessSettings PostProcessSettings;
	
	virtual void ModifyCamera(float deltaTime, FVector viewLocation, FRotator viewRotation, float fov, FVector& newViewLocation, FRotator& newViewRotation, float& newFOV) override;

	virtual void ModifyPostProcess(float deltaTime, float& postProcessBlendWeight, FPostProcessSettings& postProcessSettings) override;
};
