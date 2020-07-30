// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UBossAnimInstance();

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "AnimationProperties")
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	class ABoss* Boss;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	bool bShouldRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float OriginalRotateInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	bool bShouldJumpMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float JumpMoveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Jump")
	float OriginalDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float PlayerDistanceOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	bool bDebugLine;
};
