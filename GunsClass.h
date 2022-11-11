// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunsClass.generated.h"

class ABullet;
UCLASS()
class SPECTER_API AGunsClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunsClass();
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category = "Combat")
		int32 MaxAmmo = 200;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category = "Combat")
		int32 AmmoLeft = 30;
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
		UAnimationAsset* ShootAnim;

	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleParticle;

	UPROPERTY(EditAnywhere)
		float MaxRange = 1200.f; //range for bullet

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABullet> BP_Bullet;//returns bullet class
	UPROPERTY()
		ABullet* BulletObject;
	float BulletLifeSpan = 4.f;
	/*UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* ProjectileSpawnPoint;*/
		
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void PullTrigger();

};
