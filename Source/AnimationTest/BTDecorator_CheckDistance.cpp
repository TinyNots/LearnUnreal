// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckDistance.h"
#include "BossAIController.h"
#include "Boss.h"
#include "MainPlayer.h"

UBTDecorator_CheckDistance::UBTDecorator_CheckDistance() : Super()
{
	NodeName = "CheckDistance";
	DistanceTrigger = 100.0f;
}

void UBTDecorator_CheckDistance::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTDecorator_CheckDistance::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

bool UBTDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ABossAIController* BossAI = Cast<ABossAIController>(OwnerComp.GetAIOwner());
	ABoss* Boss = Cast<ABoss>(BossAI->GetCharacter());

	float Distance = Boss->GetDistanceTo(Cast<AActor>(Boss->CombatTarget));
	if (Distance <= DistanceTrigger)
	{
		return true;
	}

	return false;
}
