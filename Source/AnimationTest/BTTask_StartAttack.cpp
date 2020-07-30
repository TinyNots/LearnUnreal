// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StartAttack.h"
#include "BossAIController.h"
#include "Boss.h"

UBTTask_StartAttack::UBTTask_StartAttack() : Super()
{

}

void UBTTask_StartAttack::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTTask_StartAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABossAIController* BossAI = Cast<ABossAIController>(OwnerComp.GetAIOwner());
	ABoss* Boss = Cast<ABoss>(BossAI->GetCharacter());

	if (Boss->bIsAttacking)
	{
		return EBTNodeResult::Succeeded;
	}

	if (bIsJumpAttack)
	{
		Boss->StartJumpAttack();
		return EBTNodeResult::Succeeded;
	}

	Boss->StartAttack();
	return EBTNodeResult::Succeeded;
}
