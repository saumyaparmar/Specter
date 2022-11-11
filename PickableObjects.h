// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableObjects.generated.h"

UCLASS()
class SPECTER_API APickableObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
		USceneComponent* Root;
	
public:	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		UStaticMeshComponent* PickupObjectMesh;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
