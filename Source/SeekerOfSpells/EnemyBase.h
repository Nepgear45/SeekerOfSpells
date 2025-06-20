// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class SEEKEROFSPELLS_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	float Health;

	UPROPERTY(BlueprintReadOnly)
	bool Death;

	UFUNCTION(BlueprintCallable, Category = "EnemyHandler")
	void TakeDamage(float Amount);
	UFUNCTION(BlueprintCallable, Category = "EnemyHandler")
	float GetHealth();
	UFUNCTION(BlueprintCallable, Category = "EnemyHandler")
	void SetHealth(float Amount);
	UFUNCTION(BlueprintCallable, Category = "EnemyHandler")
	bool GetDeath();
};
