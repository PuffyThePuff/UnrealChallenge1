// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryBase.h"

// Sets default values
AFactoryBase::AFactoryBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	this->RootComponent = this->Mesh;

	this->Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AFactoryBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFactoryBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

