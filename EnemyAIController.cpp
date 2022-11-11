// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(AIBehavior);	
	//SetFocus(ActorPawn);
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AIBehavior != nullptr)
	{
		/*ActorPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);		
		GetBlackboardComponent()->SetValueAsVector(TEXT("Player Location"),
			ActorPawn->GetActorLocation());*/

	}
	//MoveToActor(ActorPawn, 200);
}
