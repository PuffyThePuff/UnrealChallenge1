// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "TruckActor.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealChallenge1GameModeBase.generated.h"

/**
 * 
 */

UCLASS()
class UNREALCHALLENGE1_API AUnrealChallenge1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	std::list<ATruckActor*> truckList;
	std::list<FVector*> deliveryList;

	// UI ONLY
	int woodCount = 0;
	int ironCount = 0;
	int coalCount = 0;
	int steelCount = 0;

public:
	// returns true if the delivery is accepted and a truck is sent, false if not
	bool sendTruckTo(FVector location);

	// updates the material counter hud
	void updateMaterialCount(int numberOfMaterials, std::string materialName);
};
