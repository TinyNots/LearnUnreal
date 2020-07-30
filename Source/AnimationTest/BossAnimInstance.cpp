// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "Boss.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainPlayer.h"
#include "DrawDebugHelpers.h"

UBossAnimInstance::UBossAnimInstance()
{
	OriginalRotateInterpSpeed = 0.0f;
	bDebugLine = false;
}

void UBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Boss = Cast<ABoss>(TryGetPawnOwner());

	bShouldRotate = false;
	bShouldJumpMove = false;
}

void UBossAnimInstance::UpdateAnimationProperties()
{
	if (Boss)
	{
		MovementSpeed = FVector::DotProduct(Boss->GetVelocity(), Boss->GetActorForwardVector());
		Direction = FVector::DotProduct(Boss->GetVelocity(), Boss->GetActorRightVector());

		if (bShouldRotate)
		{
			FRotator NewRotation = UKismetMathLibrary::RInterpTo(
				Boss->GetActorRotation(),
				UKismetMathLibrary::MakeRotFromX(Boss->CombatTarget->GetActorLocation() - Boss->GetActorLocation()),
				GetWorld()->GetDeltaSeconds(),
				RotationInterpSpeed * GetWorld()->GetDeltaSeconds());

			Boss->SetActorRotation(FRotator(Boss->GetActorRotation().Pitch, NewRotation.Yaw, Boss->GetActorRotation().Roll));
		}

		if (bShouldJumpMove)
		{
			float Distance = Boss->DistanceToCombatTarget;
			float JumpMoveInterpSpeed = JumpMoveSpeed * (FMath::Clamp(Distance - PlayerDistanceOffset, 0.0f, OriginalDistance) / OriginalDistance);

			if (JumpMoveInterpSpeed > 0.0f)
			{
				FVector NewLocation = UKismetMathLibrary::VInterpTo(
					Boss->GetActorLocation(),
					Boss->CombatTarget->GetActorLocation(),
					GetWorld()->GetDeltaSeconds(),
					JumpMoveInterpSpeed);

				Boss->SetActorLocation(NewLocation);
			}
		}

		if (Boss && Boss->CombatTarget && bDebugLine)
		{
			FVector BossLocation = Boss->GetActorLocation();
			FVector PlayerLocation = Boss->CombatTarget->GetActorLocation();

			FVector FBP = (BossLocation - PlayerLocation).GetSafeNormal();
			FVector NewLocation = FVector(PlayerLocation + FBP * PlayerDistanceOffset);

			DrawDebugLine(GetWorld(), Boss->CombatTarget->GetActorLocation(), NewLocation, FColor::Red);
		}
	}
}