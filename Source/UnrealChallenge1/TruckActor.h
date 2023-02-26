// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TruckActor.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class UNREALCHALLENGE1_API ATruckActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATruckActor();

	void MoveTo(FVector pickUpLocation);

	//is the truck actor currently doing a delivery?
	bool isBusy = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh;

	FVector destination;
	int cargoNum = 0;
	std::string cargoName = "none";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
