// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Health = 30;
	this->Death = false;
	this->Tags.Add("Damagable");
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::TakeDamage(float Amount)
{
	Health = Health - Amount;
	if (Health <= 0) Death = true;
}

float AEnemyBase::GetHealth()
{
	return Health;
}

void AEnemyBase::SetHealth(float Amount)
{
	Health = Amount;
}

bool AEnemyBase::GetDeath()
{
	return Death;
}
