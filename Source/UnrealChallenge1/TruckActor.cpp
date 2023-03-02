// Fill out your copyright notice in the Description page of Project Settings.


#include "TruckActor.h"

#include "UnrealChallenge1GameModeBase.h"


// Sets default values
ATruckActor::ATruckActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->RootComponent = this->Mesh;
	this->Mesh->SetSimulatePhysics(false);

	this->GameModeBase = Cast<AUnrealChallenge1GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//this->GameModeBase->TruckActors.Add(this);
}

// Called when the game starts or when spawned
void ATruckActor::BeginPlay()
{
	Super::BeginPlay();

	//this->GameModeBase->addToTruckList(this);
}

// Called every frame
void ATruckActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPickingUp)
	{
		UE_LOG(LogTemp, Log, TEXT("picking up: %f, %f, %f"), this->pickUpLoc.X, this->pickUpLoc.Y, this->pickUpLoc.Z);
		const FVector interpPosition = FMath::VInterpConstantTo(this->RootComponent->GetComponentLocation(), this->pickUpLoc, 1, 2);

		this->RootComponent->SetWorldLocation(interpPosition);

		UE_LOG(LogTemp, Log, TEXT("picking up: %f, %f, %f"), this->RootComponent->GetRelativeLocation().X, this->RootComponent->GetRelativeLocation().Y, this->RootComponent->GetRelativeLocation().Z);

		if (this->RootComponent->GetRelativeLocation() == pickUpLoc)
		{
			UE_LOG(LogTemp, Log, TEXT("switch"));
			isPickingUp = false;
			isDelivering = true;
		}
	}
	else if (isDelivering)
	{
		UE_LOG(LogTemp, Log, TEXT("delivering: %f, %f, %f"), this->deliveryLoc.X, this->deliveryLoc.Y, this->deliveryLoc.Z);
		const FVector interpPosition = FMath::VInterpConstantTo(this->RootComponent->GetComponentLocation(), this->deliveryLoc, 1, 2);

		this->RootComponent->SetWorldLocation(interpPosition);
		if (this->RootComponent->GetComponentLocation() == this->deliveryLoc)
		{
			isDelivering = false;
			//this->GameModeBase->updateMaterialCount(1, this->materialName);
		}
	}
	// rest
	//else if (!IsBusy())
	//{
	//	const FVector interpPosition = FMath::VInterpTo(this->RootComponent->GetComponentLocation(), FVector(0, 0, 0), 2, 2);

	//	this->RootComponent->SetWorldLocation(interpPosition);
	//}
}

void ATruckActor::MoveTo(FVector pickUpLocation, FVector deliveryLocation, FString materialToDeliver)
{
	UE_LOG(LogTemp, Log, TEXT("moving"));
	this->isPickingUp = true;
	this->pickUpLoc = pickUpLocation;
	this->deliveryLoc = deliveryLocation;
	this->materialName = materialToDeliver;
}