// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_StartAttack.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UBTTask_StartAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_StartAttack();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Jump")
	bool bIsJumpAttack;
};
