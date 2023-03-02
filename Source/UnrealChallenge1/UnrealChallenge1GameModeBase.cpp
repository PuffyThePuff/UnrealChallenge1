// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealChallenge1GameModeBase.h"
#include "EngineUtils.h"

AUnrealChallenge1GameModeBase::AUnrealChallenge1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUnrealChallenge1GameModeBase::BeginPlay()
{
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATruckActor::StaticClass(), this->TruckActors);

	FindAllActors(GetWorld(), TruckActors);

	GetWorldTimerManager().SetTimer(this->WoodTimerHandle, this, &AUnrealChallenge1GameModeBase::AddMaterialWood, 5.0f, true, this->woodTimeToMake);
	GetWorldTimerManager().SetTimer(this->CoalTimerHandle, this, &AUnrealChallenge1GameModeBase::AddMaterialCoal, 5.0f, true, this->coalTimeToMake);
	GetWorldTimerManager().SetTimer(this->IronTimerHandle, this, &AUnrealChallenge1GameModeBase::AddMaterialIron, 5.0f, true, this->ironTimeToMake);
}

void AUnrealChallenge1GameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATruckActor* truckToCommand;

	//UE_LOG(LogTemp, Log, TEXT("sending truck: %d"), TruckActors.Num());

	if (!TruckActors[0]->IsBusy() && !TruckActors.IsEmpty())
	{
		int factory = FMath::RandRange(1, 4);
		truckToCommand = TruckActors[0];
		switch (factory)
		{
		case 1:
			if (this->woodCount <= 0){ break; }
			sendTruckTo(truckToCommand, woodLocation, sewingLocation, "wood");
			break;
		case 2:
			if (this->ironCount <= 0){ break; }
			sendTruckTo(truckToCommand, ironLocation, steelLocation, "iron");
			break;
		case 3:
			if (this->coalCount <= 0){ break; }
			sendTruckTo(truckToCommand, coalLocation, steelLocation, "coal");
			break;
		case 4:
			if (this->steelCount <= 0){ break; }
			sendTruckTo(truckToCommand, steelLocation, sewingLocation, "steel");
			break;
		default:
			break;
		}
	}
	else if (!TruckActors[1]->IsBusy() && !TruckActors.IsEmpty())
	{
		int factory = FMath::RandRange(1, 4);
		truckToCommand = TruckActors[1];
		switch (factory)
		{
		case 1:
			if (this->woodCount <= 0){ break; }
			sendTruckTo(truckToCommand, woodLocation, sewingLocation, "wood");
			break;
		case 2:
			if (this->ironCount <= 0){ break; }
			sendTruckTo(truckToCommand, ironLocation, steelLocation, "iron");
			break;
		case 3:
			if (this->coalCount <= 0){ break; }
			sendTruckTo(truckToCommand, coalLocation, steelLocation, "coal");
			break;
		case 4:
			if (this->steelCount <= 0){ break; }
			sendTruckTo(truckToCommand, steelLocation, sewingLocation, "steel");
			break;
		default:
			break;
		}
	}

	// check materials here
	// furnace
	if (furnaceMatCountCoal > 0 && furnaceMatCountIron > 0)
	{
		GetWorldTimerManager().SetTimer(this->SteelTimerHandle, this, &AUnrealChallenge1GameModeBase::AddMaterialSteel, 1.0f, false, this->steelTimeToMake);
	}
	if (sewingFactoryMatCountSteel > 0 && sewingFactoryMatCountWood > 0)
	{
		GetWorldTimerManager().SetTimer(this->SteelTimerHandle, this, &AUnrealChallenge1GameModeBase::AddSewingMachine, 1.0f, false, this->sewingTimeToMake);
	}

	//check truck status
	if (!TruckActors[0]->IsBusy() && TruckActors[0]->materialName != "")
	{
		updateMaterialCount(1, TruckActors[0]->materialName);
		UE_LOG(LogTemp, Log, TEXT("delivered: %s"), *TruckActors[0]->materialName);
		TruckActors[0]->materialName = "";
	}
	if (!TruckActors[1]->IsBusy() && TruckActors[1]->materialName != "")
	{
		updateMaterialCount(1, TruckActors[1]->materialName);
		UE_LOG(LogTemp, Log, TEXT("delivered: %s"), *TruckActors[1]->materialName);
		TruckActors[1]->materialName = "";
	}
}

void AUnrealChallenge1GameModeBase::sendTruckTo(ATruckActor* truck, FVector pickUpLocation, FVector deliveryLocation, FString matName)
{
	UE_LOG(LogTemp, Log, TEXT("sending truck"));
	truck->MoveTo(pickUpLocation, deliveryLocation, matName);
}

void AUnrealChallenge1GameModeBase::updateMaterialCount(int numberOfMaterials, FString materialName)
{
	if (materialName == "wood")
	{
		this->woodCount -= numberOfMaterials;
		this->sewingFactoryMatCountWood += numberOfMaterials;
		UE_LOG(LogTemp, Log, TEXT("wood: %d"), this->woodCount);
	}
	if (materialName == "iron")
	{
		this->ironCount -= numberOfMaterials;
		this->furnaceMatCountIron += numberOfMaterials;
		UE_LOG(LogTemp, Log, TEXT("iron: %d"), this->ironCount);
	}
	if (materialName == "coal")
	{
		this->coalCount -= numberOfMaterials;
		this->furnaceMatCountCoal += numberOfMaterials;
		UE_LOG(LogTemp, Log, TEXT("coal: %d"), this->coalCount);
	}
	if (materialName == "steel")
	{
		this->steelCount -= numberOfMaterials;
		this->sewingFactoryMatCountSteel += numberOfMaterials;		  
		UE_LOG(LogTemp, Log, TEXT("steel: %d"), this->steelCount);
	}
}

void AUnrealChallenge1GameModeBase::addToTruckList(ATruckActor* actorToAdd)
{
	this->TruckActors.Push(actorToAdd);
}

void AUnrealChallenge1GameModeBase::AddMaterialWood()
{
	UE_LOG(LogTemp, Log, TEXT("wood added"));
	this->woodCount++;
	if (this->woodCount > 3) { this->woodCount = 3; }
}

void AUnrealChallenge1GameModeBase::AddMaterialIron()
{
	UE_LOG(LogTemp, Log, TEXT("iron added"));
	this->ironCount++;
	if (this->ironCount > 3) { this->ironCount = 3; }
}

void AUnrealChallenge1GameModeBase::AddMaterialCoal()
{
	UE_LOG(LogTemp, Log, TEXT("coal added"));
	this->coalCount++;
	if (this->coalCount > 3) { this->coalCount = 3; }
}

void AUnrealChallenge1GameModeBase::AddMaterialSteel()
{
	UE_LOG(LogTemp, Log, TEXT("steel added"));
	this->steelCount++;
	if (this->steelCount > 3) { this->steelCount = 3; }
}

void AUnrealChallenge1GameModeBase::AddSewingMachine()
{
	//UE_LOG(LogTemp, Log, TEXT("sewing machine added"));
}

float AUnrealChallenge1GameModeBase::TimeLeft(FString materialName)
{
	if (materialName == "wood")
	{
		return GetWorldTimerManager().GetTimerRemaining(WoodTimerHandle) / woodTimeToMake;
	}
	if (materialName == "iron")
	{
		return GetWorldTimerManager().GetTimerRemaining(IronTimerHandle) / ironTimeToMake;
	}
	if (materialName == "coal")
	{
		return GetWorldTimerManager().GetTimerRemaining(CoalTimerHandle) / coalTimeToMake;
	}
	if (materialName == "steel")
	{
		return GetWorldTimerManager().GetTimerRemaining(SteelTimerHandle) / steelTimeToMake;
	}

	return 0;
}
