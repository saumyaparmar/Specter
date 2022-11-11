// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GunsClass.h"
#include "GameFramework/DamageType.h"
#include "TimerManager.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->OnComponentHit.AddDynamic(this,&ABullet::OnHit); //Adding functions to OnComponentHit Delegate
	BulletMesh->AddImpulse(GetActorForwardVector() * BulletForce);
	SetLifeSpan(5);
}
// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void ABullet::DestroyBullet()
{
	Destroy();
}
void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	AActor* MyOwner = GetOwner(); // Getting owner for our bullet
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, HitResult.ImpactPoint);
	if (MyOwner == nullptr)//checking if owner is nullptr then return and destroy
	{
		Destroy(); 
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Owner: %s"), *(MyOwner->GetName()));
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController(); //Returns our player, gun is controlled by player
	UClass* DamageType = UDamageType::StaticClass(); //return uclass pointer which new class will represent DamageType class
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)//Check if HitActor exists,not this bullet,and not it's owner
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, MyOwner, DamageType); //Apply damage to actor which bullet hits
		GetWorldTimerManager().SetTimer(DestroyBulletHandle, this,&ABullet::DestroyBullet, 0.1f, false);
	}
}

