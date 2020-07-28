// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATIONTEST_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	
	UFUNCTION(BlueprintCallable, Category = "AnimationProperties")
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	class AMainPlayer* Player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	float Direction;

	UFUNCTION()
	void RotationForDirectionRoll();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	bool bShouldRotate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RollSetting")
	float MaxDegreePerSecond;

	UFUNCTION(BlueprintCallable)
	void StartRotateLimit(float MaxPossibleRotationIn, float MaxDegreePerSecondIn);
};
