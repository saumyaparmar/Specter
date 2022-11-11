// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPECTER_API UHealthComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:

	

	UFUNCTION(BlueprintCallable)
		void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
			class AController* Instigator//if damaged caused by player controlling the pawn, then instigator is the controller
			, AActor* DamageCauser);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Health")
		float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health = 0.f;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
