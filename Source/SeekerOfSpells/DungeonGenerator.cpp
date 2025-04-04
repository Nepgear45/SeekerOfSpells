// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"
#include <random>
#include <string>

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FActorSpawnParameters ADungeonGenerator::SpawnParameters(int x)
{
	FActorSpawnParameters SP;

	switch (x)
	{
	case 0:
		SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		break;
	case 1:
		SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		break;
	case 2:
		SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		break;
	case 3:
		SP.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		break;
	}

	return SP;
}

FVector ADungeonGenerator::GetRoomSize(AActor* Room)
{
	FVector Size = FVector(Room->GetComponentsBoundingBox().GetSize());

	return Size;
}

float ADungeonGenerator::VectorDistance(FVector x, FVector y)
{
	float a = x.X - y.X;
	float b = x.Y - y.Y;

	return sqrt((a * a) + (b * b));
}

void ADungeonGenerator::GenerateRoomTypes(int x, FVector GenLoc)
{
	//Need to consider bit shifting although that might be optimization overkill since this needs to be preloaded anyway to reduce lag at the start of the game
	// 
	//Room finding Index
	// 0 = no room
	// 1 = room allocated no type

	/*
	* --------- Room Type declaration Index ---------
	*
	* 2 = N
	* 3 = E
	* 4 = S
	* 5 = W
	* 6 = N + E
	* 7 = N + S
	* 8 = N + W
	* 9 = E + S
	*10 = E + W
	*11 = S + W
	*12 = N + E + S
	*13 = N + E + W
	*14 = N + S + W
	*15 = E + S + W
	*16 = N + E + S + W
	*
	*/

	int Index = 0;
	int RoomCount = 0;
	TArray<bool> RoomDir; //N + E + S + W
	RoomDir.Init(false, 4);

	int Offset = x + x + 1;
	FVector TempBossRoomLoc = FVector(0.f, 0.f, 0.f);

	for (int j = 0; j < RoomTypesAllowed.Num(); j++)
	{
		RoomDir[0] = false;
		RoomDir[1] = false;
		RoomDir[2] = false;
		RoomDir[3] = false;
		RoomCount = 0;

		if (RoomTypesAllowed[Index] != 0)
		{
			if ((Index - Offset) > 0) //More optimal than isValid
			{
				if (RoomTypesAllowed[Index - Offset] != 0) // Checks North
				{
					RoomDir[0] = true;
					RoomCount++;
				}
			}
			if ((Index + 1) < RoomTypesAllowed.Num())
			{
				if (RoomTypesAllowed[Index + 1] != 0) // Checks East
				{
					RoomDir[1] = true;
					RoomCount++;
				}
			}
			if ((Index + Offset) < RoomTypesAllowed.Num())
			{
				if (RoomTypesAllowed[Index + Offset] != 0) // Checks South
				{
					RoomDir[2] = true;
					RoomCount++;
				}
			}
			if ((Index - 1) > 0)
			{
				if (RoomTypesAllowed[Index - 1] != 0) // Checks West
				{
					RoomDir[3] = true;
					RoomCount++;
				}
			}

			int Temp = 0;

			switch (RoomCount) //Filters the amount of rooms for optimization
			{
			case 1:
				//2 - 5
				while (!RoomDir[Temp]) Temp++;
				Temp = Temp + 2;
				if (VectorDistance(TempBossRoomLoc, GenLoc) < VectorDistance(RoomLocations[Index], GenLoc))
				{
					TempBossRoomLoc = RoomLocations[Index];
					UE_LOG(LogTemp, Error, TEXT(" Boss room new loc %s"), *TempBossRoomLoc.ToString());
				}				
				RoomTypesAllowed[Index] = Temp;
				break;
			case 2:
				//6 - 8
				if ((RoomDir[0]) && (RoomDir[1])) RoomTypesAllowed[Index] = (6);
				if ((RoomDir[0]) && (RoomDir[2])) RoomTypesAllowed[Index] = (7);
				if ((RoomDir[0]) && (RoomDir[3])) RoomTypesAllowed[Index] = (8);
				//9 - 11
				if ((RoomDir[1]) && (RoomDir[2])) RoomTypesAllowed[Index] = (9);
				if ((RoomDir[1]) && (RoomDir[3])) RoomTypesAllowed[Index] = (10);
				if ((RoomDir[2]) && (RoomDir[3])) RoomTypesAllowed[Index] = (11);
				break;
			case 3:
				//12 - 15
				if ((RoomDir[0]) && (RoomDir[1]) && (RoomDir[2])) RoomTypesAllowed[Index] = (12);
				if ((RoomDir[0]) && (RoomDir[1]) && (RoomDir[3])) RoomTypesAllowed[Index] = (13);
				if ((RoomDir[0]) && (RoomDir[2]) && (RoomDir[3])) RoomTypesAllowed[Index] = (14);
				if ((RoomDir[1]) && (RoomDir[2]) && (RoomDir[3])) RoomTypesAllowed[Index] = (15);
				break;
			case 4:
				// 16
				if ((RoomDir[0]) && (RoomDir[1]) && (RoomDir[2]) && (RoomDir[3])) RoomTypesAllowed[Index] = (16);
				break;
			}
		}
		Index++;
	}
}

void ADungeonGenerator::PrintRoomLayout(int y, int FloorNum) //Debug
{
	int x = 0;
	FString Line = "";

	UE_LOG(LogTemp, Warning, TEXT(" --------------- Floor %d --------------- "), FloorNum);
	for (int i = 0; i < (y + y + 1); i++)
	{
		for (int j = 0; j < (y + y + 1); j++)
		{
			if (RoomTypesAllowed[x] <= 9) Line = Line + "  " + FString::FromInt(RoomTypesAllowed[x]);
			else Line = Line + " " + FString::FromInt(RoomTypesAllowed[x]);

			if (x < RoomTypesAllowed.Num()) x++;
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Line);
		Line = "";
	}
}

void ADungeonGenerator::GenerateDungeon(int MaxRooms, int Floors, float RoomScalingPerFloor, FVector StartLocation)
{
	NewFloorLoc = StartLocation;
	SpawnStartingRoom(NewFloorLoc);

	//for (int i = 0; i < Floors; i++)
	{
		RoomList.Empty();
		RoomList.Shrink();
		RoomList.Init(nullptr, MaxRooms);
		RoomLocations.Empty();
		RoomLocations.Shrink();
		RoomLocations.Init(FVector(0.f, 0.f, 0.f), (MaxRooms + MaxRooms + 1) * (MaxRooms + MaxRooms + 1));

		GenerateRoomLocations(MaxRooms, NewFloorLoc);
		GenerateRoomTypes(MaxRooms, NewFloorLoc);
		SpawnRooms(MaxRooms);
		PrintRoomLayout(MaxRooms, 1);
	}

	UE_LOG(LogTemp, Warning, TEXT("Starting Location: %s"), *PTR_SpawnRoom->GetActorLocation().ToString());
}

void ADungeonGenerator::SpawnStartingRoom(FVector Location)
{
	PTR_SpawnRoom = GetWorld()->SpawnActor<AActor>(SpawnRoom, Location, Rot, SpawnParameters(2));

	UE_LOG(LogTemp, Warning, TEXT("PTR to spawn room: %d"), PTR_SpawnRoom);
}

void ADungeonGenerator::GenerateRoomLocations(int MaxRooms, FVector GenPoint)
{
	FVector CurrentLoc = GenPoint;
	int Offset = MaxRooms + MaxRooms + 1;
	int CurrentIndex = (Offset * Offset) / 2;
	FVector UniformRoomSize = GetRoomSize(PTR_SpawnRoom);
	TArray<AActor*> TempActors;
	RoomTypesAllowed.Init(0, (Offset * Offset));
	RoomLocations[(Offset * Offset) / 2] = PTR_SpawnRoom->GetActorLocation();

	RoomTypesAllowed[CurrentIndex] = 30;
	UE_LOG(LogTemp, Warning, TEXT("Startpoint index num: %d"), CurrentIndex);
	for (int i = 0; i < MaxRooms; i++)
	{
		int x = rand() % 4 + 1; //Would be nice to implement better room gen choices (Maybe try true randomness)

		UE_LOG(LogTemp, Warning, TEXT("Iteration: %d"), i);
		UE_LOG(LogTemp, Warning, TEXT("Random Gen direction: %d"), x);

		//Maybe add the thrid dimension
		switch (x)
		{
		case 1: //North +X
			CurrentLoc = CurrentLoc + FVector(UniformRoomSize.X + 1, 0.f, 0.f);
			TempActors.Add(GetWorld()->SpawnActor<AActor>(NorthRoom, CurrentLoc, Rot, SpawnParameters(3)));
			if (TempActors[TempActors.Num() - 1] != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Creating room location at: %s"), *CurrentLoc.ToString())
				RoomLocations[CurrentIndex - Offset] = CurrentLoc;
				RoomTypesAllowed[CurrentIndex - Offset] = 1;
			}
			CurrentIndex = CurrentIndex - Offset;
			break;
		case 2: //East +Y
			CurrentLoc = CurrentLoc + FVector(0.f, UniformRoomSize.Y + 1, 0.f);
			TempActors.Add(GetWorld()->SpawnActor<AActor>(EastRoom, CurrentLoc, Rot, SpawnParameters(3)));
			if (TempActors[TempActors.Num() - 1] != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Creating room location at: %s"), *CurrentLoc.ToString())
				RoomLocations[CurrentIndex + 1] = CurrentLoc;
				RoomTypesAllowed[CurrentIndex + 1] = 1;
			}
			CurrentIndex = CurrentIndex + 1;
			break;
		case 3: //South -X
			CurrentLoc = CurrentLoc + FVector(-UniformRoomSize.X - 1, 0.f, 0.f);
			TempActors.Add(GetWorld()->SpawnActor<AActor>(SouthRoom, CurrentLoc, Rot, SpawnParameters(3)));
			if (TempActors[TempActors.Num() - 1] != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Creating room location at: %s"), *CurrentLoc.ToString())
				RoomLocations[CurrentIndex + Offset] = CurrentLoc;
				RoomTypesAllowed[CurrentIndex + Offset] = 1;
			}
			CurrentIndex = CurrentIndex + Offset;
			break;
		case 4: //West -Y
			CurrentLoc = CurrentLoc + FVector(0.f, -UniformRoomSize.Y - 1, 0.f);
			TempActors.Add(GetWorld()->SpawnActor<AActor>(WestRoom, CurrentLoc, Rot, SpawnParameters(3)));
			if (TempActors[TempActors.Num() - 1] != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Creating room location at: %s"), *CurrentLoc.ToString())
				RoomLocations[CurrentIndex - 1] = CurrentLoc;
				RoomTypesAllowed[CurrentIndex - 1] = 1;
			}
			CurrentIndex = CurrentIndex - 1;
			break;
		}
	}

	for (int i = 0; i < TempActors.Num(); i++) if (TempActors[i] != nullptr) TempActors[i]->Destroy(); //Destroy all temp actors
	TempActors.Empty();
}

void ADungeonGenerator::SpawnRooms(int MaxRooms)
{
	int TempInt = 0;
	for (int i = 0; i < RoomTypesAllowed.Num(); i++)
	{
		TempInt = RoomTypesAllowed[i];

		switch (TempInt)
		{
		case 0: //No room
			break;
		case 1: //This should never happen
			UE_LOG(LogTemp, Error, TEXT("Room type 1 | Room has been uninitialized"));
			break;
		case 2: //Single Door
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeSingleN[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 3:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeSingleE[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 4:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeSingleS[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 5:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeSingleW[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 6: //Double Door
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeDoubleNE[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 7:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeDoubleNS[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 8:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeDoubleNW[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 9:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeDoubleES[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 10:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeDoubleEW[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 11:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypeDoubleSW[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 12: //Triple Door
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypesTripleNES[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 13:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypesTripleNEW[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 14:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypesTripleNSW[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 15:
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypesTripleESW[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 16: //Quad Door
			RoomList.Add(GetWorld()->SpawnActor<AActor>(RoomTypesQuadrupleNESW[0], RoomLocations[i], Rot, SpawnParameters(3)));
			break;
		case 17:
			break;
		case 18:
			break;
		case 19:
			break;
		case 20:
			break;
		case 30: //SpawnRoom
			UE_LOG(LogTemp, Error, TEXT("Spawn room, should never be called."));
			break;
		}
	}
}

