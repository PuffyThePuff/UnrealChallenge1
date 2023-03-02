// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TruckActor.generated.h"

class AUnrealChallenge1GameModeBase;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UNREALCHALLENGE1_API ATruckActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATruckActor();

	void MoveTo(FVector pickUpLocation, FVector deliveryLocation, FString materialToDeliver);
	bool IsBusy() const;

	//is the truck actor currently doing a delivery?
	bool isDelivering = false;
	bool isPickingUp = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AUnrealChallenge1GameModeBase* GameModeBase;

	FVector pickUpLoc;
	FVector deliveryLoc;
	int cargoNum = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString materialName = "";
};

inline bool ATruckActor::IsBusy() const
{
	if (isDelivering || isPickingUp)
	{
		UE_LOG(LogTemp, Log, TEXT("truck is busy"));
		return true;
	}
	UE_LOG(LogTemp, Log, TEXT("truck is not busy"));
	return false;
}
