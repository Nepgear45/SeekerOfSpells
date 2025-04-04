// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

UCLASS()
class SEEKEROFSPELLS_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FActorSpawnParameters SpawnParameters(int x);
	FVector GetRoomSize(AActor* Room);
	float VectorDistance(FVector x, FVector y);
	void GenerateRoomTypes(int x, FVector GenLoc);
	void PrintRoomLayout(int y, int FloorNum);
	UPROPERTY()
	FVector NewFloorLoc;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Room pointers
	UPROPERTY()
	AActor* PTR_SpawnRoom;
	UPROPERTY()
	TArray<AActor*> RoomList;
	UPROPERTY()
	TArray<AActor*> AllRoomList;
	UPROPERTY()
	TArray<FVector> RoomLocations;
	UPROPERTY()
	TArray<int8> RoomTypesAllowed;

	// ------------------------ Room actors ------------------------ 
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawnRoom;

	//Rooms with single enterances
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeSingleN;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeSingleE;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeSingleS;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeSingleW;

	//Rooms with double enterances
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeDoubleNE;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeDoubleNS;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeDoubleNW;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeDoubleES;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeDoubleEW;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypeDoubleSW;

	//Rooms with triple enterances
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypesTripleNES;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypesTripleNEW;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypesTripleNSW;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypesTripleESW;

	//Rooms with quadruple enterances
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RoomTypesQuadrupleNESW;

	//Debug rooms
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> NorthRoom;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EastRoom;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SouthRoom;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WestRoom;


	//Given Variables
	UPROPERTY(EditAnywhere)
	FRotator Rot;


	UFUNCTION(BlueprintCallable, Category = "RoomGen")
	void GenerateDungeon(int MaxRooms, int Floors, float RoomScalingPerFloor, FVector StartLocation);

	UFUNCTION(BlueprintCallable, Category = "RoomGen")
	void SpawnStartingRoom(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "RoomGen")
	void GenerateRoomLocations(int MaxRooms, FVector GenPoint);

	UFUNCTION(BlueprintCallable, Category = "RoomGen")
	void SpawnRooms(int MaxRooms);
};
