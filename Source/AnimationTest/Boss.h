// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"

UCLASS()
class ANIMATIONTEST_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss();

	UPROPERTY(EditAnywhere, Category = "Behavior")
	class UBehaviorTree* BotBehavior;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boss")
	class UStaticMeshComponent* WeaponStaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	class UAnimMontage* CombatMontage;

	void StartAttack();

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDebugSpecificAttacak;

	UPROPERTY(EditAnywhere, Category = "Debug")
	int SpecificAttackNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	bool bIsAttacking;

	UFUNCTION()
	void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	class AMainPlayer* CombatTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boss")
	class ABossAIController* BossAI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float CombatRange;

	void OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	int OldAttackNumber;

	void StartJumpAttack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	float DistanceToCombatTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float JumpAttackRange;
};
