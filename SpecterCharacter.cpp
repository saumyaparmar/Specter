// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecterCharacter.h"
#include "GunsClass.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
ASpecterCharacter::ASpecterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ASpecterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GunMeshRotation = Gun->Mesh->GetSocketRotation(TEXT("MuzzleFlash"));
	HitStartLoc = Gun->Mesh->GetSocketLocation(TEXT("MuzzleFlash"));
	HitEndLoc = HitStartLoc + GunMeshRotation.Vector()*HitMaxRange;
	bool isHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		HitStartLoc,
		HitEndLoc,
		ECollisionChannel::ECC_GameTraceChannel2);
	if (isHit)
	{
		if (HitResult.GetActor()->ActorHasTag("Pickable"))
		{
			isPickable = true;
			//UE_LOG(LogTemp, Warning, TEXT("Hit Success"));
		}
		else
		{
			isPickable = false;
		}
		
	}
	else
	{
		isPickable = false;
	}
}
void ASpecterCharacter::BeginPlay()
{
	
	Super::BeginPlay();
	if (GunClass)
	{
		Gun = GetWorld()->SpawnActor<AGunsClass>(GunClass);
		if (Gun)
		{
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Attach_Weapon")); //Attaching Weapon to Socket
			Gun->SetOwner(this);
		}
	}
	if (Gun == nullptr)
	{
		return;
	}
	LoadedAmmo = Gun->AmmoLeft;
	AmmoPool = Gun->MaxAmmo;
}
// Called to bind functionality to input
void ASpecterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Axis Bindings
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASpecterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASpecterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASpecterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ASpecterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ASpecterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ASpecterCharacter::LookRightRate);

	//Action Bindings
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASpecterCharacter::Crouching);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &ASpecterCharacter::Crouching);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ASpecterCharacter::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &ASpecterCharacter::StopFire);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &ASpecterCharacter::Reload);
}
void ASpecterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ASpecterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASpecterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ASpecterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->DeltaTimeSeconds);
}

void ASpecterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ASpecterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->DeltaTimeSeconds);
}

void ASpecterCharacter::JumpMovement()
{
	Jump();
}

void ASpecterCharacter::Crouching()
{
	if (isCrounching == false)
	{
		CharacterMovements->MaxWalkSpeed = CrouchSpeed;
		isCrounching = true;
	}
	else
	{
		CharacterMovements->MaxWalkSpeed = WalkSpeed;
		isCrounching = false;
	}
}

void ASpecterCharacter::FireGun()
{
	//UE_LOG(LogTemp, Warning, TEXT("True"))
	if (GetVelocity().Size() < 300 && LoadedAmmo > 0 && IsFiring)
	{
		Gun->PullTrigger();
		LoadedAmmo--;
		Gun->AmmoLeft--;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), GetVelocity().Size());
}

void ASpecterCharacter::StartFire()
{
	IsFiring = true;
	FireGun();
	if (LoadedAmmo == 0)
	{
		IsFiring = false;
		UGameplayStatics::PlaySound2D(this, OutOfAmmoSound);
	}
	else
	{
		GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ASpecterCharacter::FireGun, FireRate, true);
	}	
}

void ASpecterCharacter::StopFire()
{
	IsFiring = false;
	UE_LOG(LogTemp, Warning, TEXT("False"));
}

void ASpecterCharacter::Reload()
{
	if (Gun)
	{
		
		if ((AmmoPool - (30 - LoadedAmmo)) > 0 && LoadedAmmo != 30)
		{
			if (LoadedAmmo >= 0 && LoadedAmmo < 30 && AmmoPool != 0)
			{
				UGameplayStatics::PlaySound2D(this, ReloadSound);
			}
			Gun->MaxAmmo = Gun->MaxAmmo - (30 - Gun->AmmoLeft);
			AmmoPool = AmmoPool - (30 - LoadedAmmo);
			LoadedAmmo = 30;
			Gun->AmmoLeft = 30;
			
			//Gun->Mesh->PlayAnimation(ReloadAnim, false);
		}
		else if ((AmmoPool - (30 - LoadedAmmo)) <= 0 && LoadedAmmo != 30)
		{
			if (LoadedAmmo >= 0 && LoadedAmmo < 30 && AmmoPool != 0)
			{
				UGameplayStatics::PlaySound2D(this, ReloadSound);
			}
			UE_LOG(LogTemp,Warning,TEXT("Success"));
			LoadedAmmo = LoadedAmmo + AmmoPool;
			Gun->AmmoLeft = Gun->AmmoLeft + Gun->MaxAmmo;
			AmmoPool = 0;
			Gun->MaxAmmo = 0;
			
			//Gun->Mesh->PlayAnimation(ReloadAnim, false);
		}
		
	}
	
}

