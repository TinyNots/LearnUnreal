// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponStaticMeshComponent->SetupAttachment(Cast<USceneComponent>(GetMesh()),"hand_lSocket");

	bDebugSpecificAttacak = false;
	SpecificAttackNumber = 0;
	bIsAttacking = false;
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		AIController->RunBehaviorTree(BotBehavior);
	}
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoss::StartAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatMontage)
	{
		if (AnimInstance->Montage_IsPlaying(CombatMontage))
		{
			return;
		}

		int RandomAttackNumber = FMath::RandRange(0, 4);

		if (bDebugSpecificAttacak)
		{
			RandomAttackNumber = SpecificAttackNumber;
		}

		AnimInstance->Montage_Play(CombatMontage);

		switch (RandomAttackNumber)
		{
		case 0:
			AnimInstance->Montage_JumpToSection(TEXT("Combo01"));
			break;
		case 1:
			AnimInstance->Montage_JumpToSection(TEXT("Combo02"));
			break;
		case 2:
			AnimInstance->Montage_JumpToSection(TEXT("Combo03"));
			break;
		case 3:
			AnimInstance->Montage_JumpToSection(TEXT("Combo04"));
			break;
		case 4:
			AnimInstance->Montage_JumpToSection(TEXT("JumpAttack"));
			break;
		default:
			AnimInstance->Montage_JumpToSection(TEXT("Combo01"));
			break;
		}
	}
}