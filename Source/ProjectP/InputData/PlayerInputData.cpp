// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputData.h"

UPlayerInputData::UPlayerInputData()
{
	// context
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext>
			asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/01_InputDatas/IMC_PlayerControls.IMC_PlayerControls'"));

		if (asset.Succeeded())
			mContext = asset.Object;
	}

	// movement
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/IA_PlayerControls_Movement.IA_PlayerControls_Movement'"));

		if (asset.Succeeded())
			mInputToMovement = asset.Object;
	}

	// camera movement
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/IA_PlayerControls_CameraMovement.IA_PlayerControls_CameraMovement'"));

		if (asset.Succeeded())
			mInputToCameraMovement = asset.Object;
	}

	// jump
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/IA_PlayerControls_Jump.IA_PlayerControls_Jump'"));

		if (asset.Succeeded())
			mInputToJump = asset.Object;
	}

	// attack
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/IA_PlayerControls_Attack.IA_PlayerControls_Attack'"));

		if (asset.Succeeded())
			mInputToAttack = asset.Object;
	}
}