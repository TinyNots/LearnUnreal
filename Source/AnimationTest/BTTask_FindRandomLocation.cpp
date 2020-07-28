// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation() : Super()
{

}

void UBTTask_FindRandomLocation::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
		UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

		FVector AILocation = AIController->GetPawn()->GetActorLocation();
		FNavLocation PointNavigation;
		NavigationSystem->GetRandomPointInNavigableRadius(AILocation, 1500.0f, PointNavigation);

		Blackboard->SetValueAsVector(TEXT("TargetLocation"), PointNavigation.Location);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
