// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SPECTER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void DestroyBullet();
	FTimerHandle DestroyBulletHandle;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float Damage = 50.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float BulletForce = 50.f;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BulletMesh;
	UPROPERTY(EditAnywhere)
		UParticleSystem* ImpactEffect;
	
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp //Comp Hitting things
			, AActor* OtherActor//Actor that it hits
			, UPrimitiveComponent* OtherComp //Actor Comp that it hits
			, FVector NormalImpulse // assign Impulse to Collision Event
			, const FHitResult& HitResult);
};
