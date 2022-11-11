// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "SpecterCharacter.generated.h"
class AGunsClass;
/**
 * 
 */
UCLASS()
class SPECTER_API ASpecterCharacter : public ABaseCharacter
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//Movements
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRight(float AxisValue);
	void LookRightRate(float AxisValue);

	//Actions
	void JumpMovement();
	void Crouching();
	void FireGun();
	void StartFire();
	void StopFire();
	void Reload();
	UPROPERTY(EditAnywhere,Category = "Interact")
		float HitMaxRange = 600.f;
	UPROPERTY(EditAnywhere)
	float RotationRate = 20.f;
	
	UPROPERTY(EditDefaultsOnly,Category="Combat")
		TSubclassOf<AGunsClass> GunClass; //returns class
	UPROPERTY()
		AGunsClass* Gun; //Stores actual gun from blueprint
	UPROPERTY()
		USkeletalMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere)
		UAnimationAsset* ReloadAnim;
	
	FTimerHandle FireRateTimerHandle;
	bool IsFiring = false;
	class UCharacterMovementComponent* CharacterMovements = GetCharacterMovement();

	float WalkSpeed = 400.f;
	float CrouchSpeed = 200.f;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		FHitResult HitResult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		bool isPickable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		FVector HitStartLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		FRotator GunMeshRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		FVector HitEndLoc;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int32 LoadedAmmo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int32 AmmoPool;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float FireRate = 0.2f;
	UPROPERTY(EditAnywhere,Category = "Ammo")
		class USoundWave* OutOfAmmoSound;
	UPROPERTY(EditAnywhere, Category = "Ammo")
		class USoundWave* ReloadSound;
	ASpecterCharacter();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool isCrounching = false;
	// Called to bind functionality to input
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
