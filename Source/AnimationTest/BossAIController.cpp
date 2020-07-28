// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"

ABossAIController::ABossAIController()
{

}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ABossAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}