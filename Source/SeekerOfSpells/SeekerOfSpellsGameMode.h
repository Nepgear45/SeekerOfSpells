// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SeekerOfSpellsGameMode.generated.h"

UCLASS(minimalapi)
class ASeekerOfSpellsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASeekerOfSpellsGameMode();

private:
	UPROPERTY()
	TArray<AActor*> EnemyList;

public:
	UFUNCTION(BlueprintCallable, Category = "GameModeHanlder")
	TArray<AActor*> GetEnemyList();
	UFUNCTION(BlueprintCallable, Category = "GameModeHanlder")
	void AddToEnemyList(AActor* Enemy);

	UFUNCTION(BlueprintCallable, Category = "GameModeHanlder")
	AActor* GetEnemyAtIndex(int x);

};



