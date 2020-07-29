// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "BossAIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation() : Super()
{
	DestinationRadius = 100.0f;
}

void UBTTask_FindRandomLocation::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABossAIController* BossAIController = Cast<ABossAIController>(OwnerComp.GetAIOwner());
	if (BossAIController)
	{
		UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
		UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

		FVector BossAILocation = BossAIController->GetPawn()->GetActorLocation();
		FNavLocation PointNavigation;
		NavigationSystem->GetRandomPointInNavigableRadius(BossAILocation, DestinationRadius, PointNavigation);

		Blackboard->SetValueAsVector(TEXT("TargetLocation"), PointNavigation.Location);
		return EBTNodeResult::Succeeded;
	}
	UE_LOG(LogTemp, Warning, TEXT("Fail to find location for the enemy."));
	return EBTNodeResult::Failed;
}
