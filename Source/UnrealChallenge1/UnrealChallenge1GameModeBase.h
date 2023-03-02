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

public:
	AUnrealChallenge1GameModeBase();
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	std::list<FVector*> deliveryList;

	float woodTimeToMake = 5.0f;
	float ironTimeToMake = 5.0f;
	float coalTimeToMake = 5.0f;
	float steelTimeToMake = 2.5f;
	float sewingTimeToMake = 10.0f;

	FVector woodLocation = FVector(-400, -20, 0);
	FVector ironLocation = FVector(50, -300, 0);
	FVector coalLocation = FVector(-200, -300, 0);
	FVector steelLocation = FVector(-50, -20, 0);
	FVector sewingLocation = FVector(-200, 300, 0);

	FTimerHandle WoodTimerHandle;
	FTimerHandle IronTimerHandle;
	FTimerHandle CoalTimerHandle;
	FTimerHandle SteelTimerHandle;
	FTimerHandle SewingTimerHandle;

	void AddMaterialWood();
	void AddMaterialIron();
	void AddMaterialCoal();
	void AddMaterialSteel();
	void AddSewingMachine();

	template<typename T>
	void FindAllActors(UWorld* world, TArray<T*>& out);

public:
	void sendTruckTo(ATruckActor* truckActor, FVector pickUpLocation, FVector deliveryLocation, FString matName);

	// updates the material counter hud
	void updateMaterialCount(int numberOfMaterials, FString materialName);

	void addToTruckList(ATruckActor* actorToAdd);

	UFUNCTION(BlueprintCallable, Category = "Functions")
	float TimeLeft(FString materialName);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lists")
	TArray<ATruckActor*> TruckActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Count")
	int woodCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Count")
	int ironCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Count")
	int coalCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Count")
	int steelCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Count")
	int furnaceMatCountIron = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Count")
	int furnaceMatCountCoal = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Count")
	int sewingFactoryMatCountSteel = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Count")
	int sewingFactoryMatCountWood = 0;
};

template <typename T>
void AUnrealChallenge1GameModeBase::FindAllActors(UWorld* world, TArray<T*>& out)
{
	for (TActorIterator<T> It(world); It; ++It)
	{
		out.Add(*It);
	}
}
