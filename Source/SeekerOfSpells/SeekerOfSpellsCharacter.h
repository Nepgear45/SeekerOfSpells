// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SeekerOfSpellsCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASeekerOfSpellsCharacter : public ACharacter
{
	GENERATED_BODY()

	//Pawn mesh: 1st person view (arms; seen only by self)
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	//First person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	//MappingContext
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	//Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	//Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	//Change spell Input Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchSpellForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchSpellBackwardAction;
	
	//Inventory List and rotation
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray<FString> InventoryList;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int InventoryListIndex;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int MaxInventory;

	UPROPERTY(EditAnywhere, Category = "SpellCasting")
	TArray<FString> AllItemsList;

public:
	ASeekerOfSpellsCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	//Spell cycling funtions
	void CycleInventoryForward();
	void CycleInventoryBackwards();

	//Spell Getter
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int GetInventoryIndex();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FString GetInventoryItemNameAtIndex(int x);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int MatchInventoryItemWithSpell(FString x);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FString PlaceItemInInventory(FString ItemName);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FString> GetAllItemsList();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

