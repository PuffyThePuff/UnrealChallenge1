// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealChallenge1GameModeBase.h"

void AUnrealChallenge1GameModeBase::BeginPlay()
{
}

bool AUnrealChallenge1GameModeBase::sendTruckTo(FVector location)
{
	if (!truckList.front()->isBusy)
	{
		truckList.front()->MoveTo(location);
		return true;
	}
	else if (!truckList.back()->isBusy)
	{
		truckList.back()->MoveTo(location);
		return true;
	}

	return false;
}

void AUnrealChallenge1GameModeBase::updateMaterialCount(int numberOfMaterials, std::string materialName)
{
	if (materialName == "wood")
	{
		this->woodCount += numberOfMaterials;
	}
	else if (materialName == "iron")
	{
		this->ironCount += numberOfMaterials;
	}
	else if (materialName == "coal")
	{
		this->coalCount += numberOfMaterials;
	}
	else if (materialName == "steel")
	{
		this->steelCount += numberOfMaterials;
	}
}
