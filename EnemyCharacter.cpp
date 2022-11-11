// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "GunsClass.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GunMeshRotation = Gun->Mesh->GetSocketRotation(TEXT("MuzzleFlash"));
	HitStartLoc = Gun->Mesh->GetSocketLocation(TEXT("MuzzleFlash"));
	HitEndLoc = HitStartLoc + GunMeshRotation.Vector() * HitMaxRange;
	
}
void AEnemyCharacter::BeginPlay()
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
void AEnemyCharacter::FireGun()
{
	if (!Gun) return;

	Gun->PullTrigger();

	/*if (GetVelocity().Size() < 300 && LoadedAmmo > 0 && IsFiring)
	{
		Gun->PullTrigger();
		LoadedAmmo--;
		Gun->AmmoLeft--;
	}*/
}
void AEnemyCharacter::StartFire()
{
	IsFiring = true;
	
	/*FireGun();
	UE_LOG(LogTemp, Warning, TEXT("Timer: %f"), (UGameplayStatics::GetTimeSeconds(GetWorld())));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyCharacter::FireGun, FireRate, true);
	UE_LOG(LogTemp, Warning, TEXT("Timer: %f"), (UGameplayStatics::GetTimeSeconds(GetWorld())));*/
}
void AEnemyCharacter::StopFire()
{
	IsFiring = false;
}
//void AEnemyCharacter::Reload()
//{
//	if (Gun)
//	{
//
//		if ((AmmoPool - (30 - LoadedAmmo)) > 0 && LoadedAmmo != 30)
//		{
//			Gun->MaxAmmo = Gun->MaxAmmo - (30 - Gun->AmmoLeft);
//			AmmoPool = AmmoPool - (30 - LoadedAmmo);
//			LoadedAmmo = 30;
//			Gun->AmmoLeft = 30;
//			//Gun->Mesh->PlayAnimation(ReloadAnim, false);
//		}
//		else if ((AmmoPool - (30 - LoadedAmmo)) <= 0 && LoadedAmmo != 30)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Success"));
//			LoadedAmmo = LoadedAmmo + AmmoPool;
//			Gun->AmmoLeft = Gun->AmmoLeft + Gun->MaxAmmo;
//			AmmoPool = 0;
//			Gun->MaxAmmo = 0;
//			//Gun->Mesh->PlayAnimation(ReloadAnim, false);
//		}
//
//	}
//}
//void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	//Action Bindings;
//	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AEnemyCharacter::StartFire);
//	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &AEnemyCharacter::StopFire);
//	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AEnemyCharacter::Reload);
//}
//
