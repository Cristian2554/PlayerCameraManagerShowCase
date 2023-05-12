// Fill out your copyright notice in the Description page of Project Settings.


#include "CMT_TopDownModifier.h"

#include "CameraManagerTest/CMT_PlayerController.h"

UCMT_TopDownModifier::UCMT_TopDownModifier(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{

}

void UCMT_TopDownModifier::ModifyCamera(float deltaTime, FVector viewLocation, FRotator viewRotation, float fov,
                                         FVector& newViewLocation, FRotator& newViewRotation, float& newFOV)
{
	Super::ModifyCamera(deltaTime, viewLocation, viewRotation, fov, newViewLocation, newViewRotation, newFOV);

 	newViewLocation = viewLocation + LocationParams.LocationOffset;
 	newViewRotation = LocationParams.RotationOverride;
	
}

void UCMT_TopDownModifier::ModifyPostProcess(float deltaTime, float& postProcessBlendWeight,
	FPostProcessSettings& postProcessSettings)
{
	Super::ModifyPostProcess(deltaTime, postProcessBlendWeight, postProcessSettings);

	postProcessSettings = PostProcessSettings;
	postProcessBlendWeight = 1.0f;
}