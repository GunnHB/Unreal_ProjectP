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
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_Movement.IA_PlayerControls_Movement'"));

		if (asset.Succeeded())
			mInputToMovement = asset.Object;
	}

	// camera movement
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_CameraMovement.IA_PlayerControls_CameraMovement'"));

		if (asset.Succeeded())
			mInputToCameraMovement = asset.Object;
	}

	// jump
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_Jump.IA_PlayerControls_Jump'"));

		if (asset.Succeeded())
			mInputToJump = asset.Object;
	}

	// light attack
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_Attack_Light.IA_PlayerControls_Attack_Light'"));

		if (asset.Succeeded())
			mInputToLightAttack = asset.Object;
	}

	// heavy attack
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_Attack_Heavy.IA_PlayerControls_Attack_Heavy'"));

		if (asset.Succeeded())
			mInputToHeavyAttack = asset.Object;
	}

	// focus
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_Focus.IA_PlayerControls_Focus'"));

		if (asset.Succeeded())
			mInputToFocus = asset.Object;
	}
	
	// draw sheath
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_DrawSheath.IA_PlayerControls_DrawSheath'"));

		if (asset.Succeeded())
			mInputToDrawSheath = asset.Object;
	}

	// interact
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_Interact.IA_PlayerControls_Interact'"));

		if (asset.Succeeded())
			mInputToInteract = asset.Object;
	}

	// dodge
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_Dodge.IA_PlayerControls_Dodge'"));

		if (asset.Succeeded())
			mInputToDodge = asset.Object;
	}

	// sprint
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_Sprint.IA_PlayerControls_Sprint'"));

		if (asset.Succeeded())
			mInputToSprint = asset.Object;
	}

	// inventory
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_UI/IA_UI_Inventory.IA_UI_Inventory'"));

		if (asset.Succeeded())
			mInputToInventory = asset.Object;
	}

	// equipment
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_UI/IA_UI_MainEquipment.IA_UI_MainEquipment'"));

		if (asset.Succeeded())
			mInputToMainEquipment = asset.Object;
	}
	
	// use item
	{
		static ConstructorHelpers::FObjectFinder<UInputAction>
			asset(TEXT("/Script/EnhancedInput.InputAction'/Game/01_InputDatas/InputAction_Control/IA_PlayerControls_UseItem.IA_PlayerControls_UseItem'"));

		if (asset.Succeeded())
			mInputToUseItem = asset.Object;
	}
}