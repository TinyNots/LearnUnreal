// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChasePlayer.h"
#include "AIController.h"
#include "MainPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Boss.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer() : Super()
{

}

void UBTTask_ChasePlayer::OnGameplayTaskActivated(UGameplayTask & Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AMainPlayer* Player = Cast <AMainPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	ABoss* Boss = Cast<ABoss>(AIController->GetCharacter());

	if (Boss->bIsAttacking)
	{
		return EBTNodeResult::InProgress;
	}

	AIController->MoveToLocation(Player->GetActorLocation());
	return EBTNodeResult::Succeeded;
}