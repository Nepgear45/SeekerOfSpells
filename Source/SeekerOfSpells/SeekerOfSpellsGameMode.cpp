// Copyright Epic Games, Inc. All Rights Reserved.

#include "SeekerOfSpellsGameMode.h"
#include "SeekerOfSpellsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASeekerOfSpellsGameMode::ASeekerOfSpellsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
