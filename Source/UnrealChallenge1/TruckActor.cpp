// Fill out your copyright notice in the Description page of Project Settings.


#include "TruckActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATruckActor::ATruckActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	this->RootComponent = this->Mesh;

	this->Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ATruckActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATruckActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->RootComponent->GetComponentLocation() != this->destination)
	{
		//FVector interpPosition;

		//interpPosition = FMath::FInterpTo(this->RootComponent->GetComponentLocation(), this->destination, 2, 2);

		//this->RootComponent->SetWorldLocation(interpPosition);
	}
	else
	{
		this->isBusy = false;
	}
}

void ATruckActor::MoveTo(FVector pickUpLoc)
{
	this->isBusy = true;
	this->destination = pickUpLoc;
}