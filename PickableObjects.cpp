// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableObjects.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickableObjects::APickableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	PickupObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	PickupObjectMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void APickableObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickableObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


