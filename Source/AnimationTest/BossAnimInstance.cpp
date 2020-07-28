// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "Boss.h"

void UBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Boss = Cast<ABoss>(TryGetPawnOwner());
}

void UBossAnimInstance::UpdateAnimationProperties()
{
	if (Boss)
	{
		MovementSpeed = FVector::DotProduct(Boss->GetVelocity(), Boss->GetActorForwardVector());
		Direction = FVector::DotProduct(Boss->GetVelocity(), Boss->GetActorRightVector());
	}
}