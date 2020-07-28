// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MainPlayer.h"
#include "Kismet/KismetMathLibrary.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	if (!Player)
	{
		Player = Cast<AMainPlayer>(TryGetPawnOwner());
	}

	bShouldRotate = false;
}

void UPlayerAnimInstance::UpdateAnimationProperties()
{
	if (Player)
	{
		MovementSpeed = FVector::DotProduct(Player->GetVelocity(), Player->GetActorForwardVector());
		Direction = FVector::DotProduct(Player->GetVelocity(), Player->GetActorRightVector());

		RotationForDirectionRoll();
	}
}

void UPlayerAnimInstance::RotationForDirectionRoll()
{
	if (Player->bIsRolling)
	{
		FRotator NewRotation = UKismetMathLibrary::RInterpTo(
			Player->GetActorRotation(),
			Player->GetDesiredRotation(),
			GetWorld()->GetDeltaSeconds(),
			MaxDegreePerSecond);

		Player->SetActorRotation(FRotator(Player->GetActorRotation().Pitch, NewRotation.Yaw, Player->GetActorRotation().Roll));
	}
}

void UPlayerAnimInstance::StartRotateLimit(float MaxPossibleRotationIn, float MaxDegreePerSecondIn)
{
	MaxDegreePerSecond = MaxDegreePerSecondIn * GetWorld()->GetDeltaSeconds();
	bShouldRotate = true;
}