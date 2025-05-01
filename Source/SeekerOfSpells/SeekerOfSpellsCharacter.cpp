// Copyright Epic Games, Inc. All Rights Reserved.

#include "SeekerOfSpellsCharacter.h"
#include "SeekerOfSpellsProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASeekerOfSpellsCharacter

ASeekerOfSpellsCharacter::ASeekerOfSpellsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	InventoryList.Init("Empty", 5);
	InventoryListIndex = 0;
	InventoryList[0] = "FireBall";
	InventoryList[1] = "FireBall";
	InventoryList[2] = "FireBall";
	InventoryList[3] = "FireBall";
	InventoryList[4] = "FireBall";

	AllItemsList.Add("BasicAttackSpell");
	AllItemsList.Add("DispellMagic");
	AllItemsList.Add("StoneCannon");
	AllItemsList.Add("FireBall");
	AllItemsList.Add("Barrier");
}

void ASeekerOfSpellsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (true) //Needs to be edited for saving
	{
		MaxInventory = 4; //Counting 0

	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ASeekerOfSpellsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASeekerOfSpellsCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASeekerOfSpellsCharacter::Look);

		// Inventory
		EnhancedInputComponent->BindAction(SwitchSpellForwardAction, ETriggerEvent::Triggered, this, &ASeekerOfSpellsCharacter::CycleInventoryForward);
		EnhancedInputComponent->BindAction(SwitchSpellBackwardAction, ETriggerEvent::Triggered, this, &ASeekerOfSpellsCharacter::CycleInventoryBackwards);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASeekerOfSpellsCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASeekerOfSpellsCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASeekerOfSpellsCharacter::CycleInventoryForward()
{
	if (Controller != nullptr)
	{
		if (InventoryListIndex < MaxInventory) InventoryListIndex++;
		else InventoryListIndex = 0;
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Inventory Index: %d"), InventoryListIndex);
	}
}

void ASeekerOfSpellsCharacter::CycleInventoryBackwards()
{
	if (Controller != nullptr)
	{
		if (InventoryListIndex >= 1) InventoryListIndex--;
		else InventoryListIndex = MaxInventory;
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Inventory Index: %d"), InventoryListIndex);
	}
}

int ASeekerOfSpellsCharacter::GetInventoryIndex()
{
	return InventoryListIndex;
}

FString ASeekerOfSpellsCharacter::GetInventoryItemNameAtIndex(int x)
{
	return InventoryList[x];
}

int ASeekerOfSpellsCharacter::MatchInventoryItemWithSpell(FString x)
{
	int Index = 0;

	for (int i = 0; i < AllItemsList.Num(); i++)
	{
		if (x == AllItemsList[i]) 
		{
			Index = i + 1;
			break;
		}
	}

	return Index;
}

FString ASeekerOfSpellsCharacter::PlaceItemInInventory(FString ItemName)
{
	if (InventoryList[InventoryListIndex] == "Empty")
	{
		InventoryList[InventoryListIndex] = ItemName;
		return FString("Empty");
	}
	else
	{
		FString Temp = InventoryList[InventoryListIndex];
		InventoryList[InventoryListIndex] = ItemName;
		return Temp;
	}
}

TArray<FString> ASeekerOfSpellsCharacter::GetAllItemsList()
{
	return AllItemsList;
}
