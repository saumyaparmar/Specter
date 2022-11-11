// Fill out your copyright notice in the Description page of Project Settings.


#include "GunsClass.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Bullet.h"
#include "TimerManager.h"

// Sets default values
AGunsClass::AGunsClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(Root);
	/*ProjectileSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);*/
	
}

// Called when the game starts or when spawned
void AGunsClass::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGunsClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGunsClass::PullTrigger()
{
	BulletObject = GetWorld()->SpawnActor<ABullet>(BP_Bullet,
		Mesh->GetSocketLocation(TEXT("MuzzleFlash")), 
		Mesh->GetSocketRotation(TEXT("MuzzleFlash")));
	BulletObject->SetOwner(this);

	/*FVector BulletInitialLocation = Mesh->GetSocketLocation(TEXT("MuzzleFlash"));
	FRotator BulletInitialRotation = Mesh->GetSocketRotation(TEXT("MuzzleFlash"));

	FVector BulletEndLocation = BulletInitialLocation + BulletInitialRotation.Vector() * MaxRange; // end point for max range of bullet

	FHitResult BulletHit;
	bool isBulletHit = GetWorld()->LineTraceSingleByChannel(BulletHit, BulletInitialLocation,
		BulletEndLocation,
		ECollisionChannel::ECC_GameTraceChannel1);
	if (isBulletHit)
	{
		//BulletObject->Destroy();
		DrawDebugLine(GetWorld(), BulletInitialLocation, BulletEndLocation, FColor::Red, true);
	}
	*/
	Mesh->PlayAnimation(ShootAnim,false);
}


