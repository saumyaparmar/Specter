// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"
class AGunsClass;
/**
 *
 */
UCLASS()
class SPECTER_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable)
		void FireGun();
	UFUNCTION(BlueprintCallable)
		void StopFire();
	UFUNCTION(BlueprintCallable)
		void StartFire();
	//void Reload();

	float HitMaxRange = 600.f;
	UPROPERTY(EditAnywhere)
		float RotationRate = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<AGunsClass> GunClass; //returns class
	UPROPERTY()
		AGunsClass* Gun; //Stores actual gun from blueprint
	UPROPERTY(BlueprintReadWrite)
		USkeletalMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere)
		UAnimationAsset* ReloadAnim;

	FTimerHandle FireRateTimerHandle;
	UPROPERTY(BlueprintReadWrite)
		bool IsFiring = false;
	UPROPERTY(BlueprintReadWrite)
	class UCharacterMovementComponent* CharacterMovements = GetCharacterMovement();

	float WalkSpeed = 400.f;
	float CrouchSpeed = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		FHitResult HitResult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		FVector HitStartLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		FRotator GunMeshRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		FVector HitEndLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 LoadedAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 AmmoPool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float FireRate = 0.2f;
	AEnemyCharacter();


	// Called to bind functionality to input
	virtual void Tick(float DeltaTime) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
};
