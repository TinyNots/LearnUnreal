// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class ANIMATIONTEST_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAcess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAcess = "true"))
	class UCameraComponent* CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Attack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveSide(float Value);

	void SprintStart();

	void SprintEnd();

	void RollStart();
	
	UFUNCTION(BlueprintCallable)
	void RollEnd();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player State")
	bool bIsRunning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Locomotion Setting")
	float WalkToMaxTime;

	UFUNCTION(BlueprintCallable)
	void VelocitySystem(float Time);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Locomotion Setting")
	float DefaultWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Locomotion Setting")
	float DefaultMaxWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player State")
	bool bIsTargetLock;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player State")
	bool bIsRolling;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CombatMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	class UAnimInstance* AnimInstance;

	UFUNCTION(BlueprintCallable)
	FRotator GetDesiredRotation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RollSetting")
	float MaxDegreePerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RollSetting")
	float MaxPossibleRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player State")
	bool bTurnToLockTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraSetting")
	float CameraInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RollSetting")
	float StepBackPower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player State")
	bool bIsBackStep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RollSetting")
	float CoolDownTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RollSetting")
	float CoolDownCounter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RollSetting")
	bool bShouldCoolDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class AWeapon* EquippedWeapon;

	void SetWeapon(class AWeapon* NewWeapon);

	class AWeapon* GetWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class AItem* SeletectedItem;

	void SetSelectedItem(class AItem* NewItem);

	class AItem* GetSelectedItem();

	void UsePickupItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class AShield* EquippedShield;

	void SetShield(class AShield* NewShield);

	class AShield* GetShield();
};
