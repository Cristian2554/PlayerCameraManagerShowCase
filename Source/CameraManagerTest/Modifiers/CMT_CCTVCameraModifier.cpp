// Fill out your copyright notice in the Description page of Project Settings.


#include "CMT_CCTVCameraModifier.h"

void UCMT_CCTVCameraModifier::ModifyCamera(float deltaTime, FVector viewLocation, FRotator viewRotation, float fov,
	FVector& newViewLocation, FRotator& newViewRotation, float& newFOV)
{
	Super::ModifyCamera(deltaTime, viewLocation, viewRotation, fov, newViewLocation, newViewRotation, newFOV);

	if (CameraOwner.Get()->GetOwningPlayerController())
	{
		newViewRotation = CameraOwner.Get()->GetOwningPlayerController()->GetControlRotation();
	}
}

void UCMT_CCTVCameraModifier::ModifyPostProcess(float deltaTime, float& postProcessBlendWeight,
	FPostProcessSettings& postProcessSettings)
{
	Super::ModifyPostProcess(deltaTime, postProcessBlendWeight, postProcessSettings);

	postProcessSettings = PostProcessSettings;
	postProcessBlendWeight = 1.0f;
}
