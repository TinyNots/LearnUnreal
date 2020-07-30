// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckTargetInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Boss.h"
#include "BossAIController.h"

UBTService_CheckTargetInRange::UBTService_CheckTargetInRange() : Super()
{

}

void UBTService_CheckTargetInRange::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTService_CheckTargetInRange::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UBTService_CheckTargetInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	ABossAIController* BossAI = Cast<ABossAIController>(OwnerComp.GetAIOwner());
	ABoss* Boss = Cast<ABoss>(BossAI->GetCharacter());

	if (Boss->DistanceToCombatTarget <= Boss->CombatRange)
	{
		Blackboard->SetValueAsBool(TEXT("IsTargetInCombatRange"), true);
	}
	else
	{
		Blackboard->SetValueAsBool(TEXT("IsTargetInCombatRange"), false);
	}

	if (Boss->DistanceToCombatTarget >= Boss->JumpAttackRange)
	{
		Blackboard->SetValueAsBool("IsTargetTooFar", true);
	}
	else
	{
		Blackboard->SetValueAsBool("IsTargetTooFar", false);
	}
}