// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckTargetInRange.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UBTService_CheckTargetInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_CheckTargetInRange();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
