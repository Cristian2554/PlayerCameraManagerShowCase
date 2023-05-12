// Fill out your copyright notice in the Description page of Project Settings.


#include "CMT_PlayerCameraManager.h"

void ACMT_PlayerCameraManager::SetCameraMode(ECameraMode newCameraMode)
{
	switch (CameraMode)
	{
	case TopDown:
		RemoveCameraModifier(FindCameraModifierByClass(TopDownCameraModifier));
		break;
	case ThirdPerson:
		RemoveCameraModifier(FindCameraModifierByClass(ThirdPersonCameraModifier));
		break;
	case CCTV:
		RemoveCameraModifier(FindCameraModifierByClass(CCTVCameraModifier));
		break;
	default:
		break;
	}

	PreviousCameraMode = CameraMode;
	CameraMode = newCameraMode;

	switch (CameraMode)
	{
	case TopDown:
		AddNewCameraModifier(TopDownCameraModifier);
		break;
	case ThirdPerson:
		AddNewCameraModifier(ThirdPersonCameraModifier);
		break;
	default:
		AddNewCameraModifier(CCTVCameraModifier);
		break;
	}
}