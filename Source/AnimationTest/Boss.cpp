// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer.h"
#include "BossAIController.h"
#include "Engine/Engine.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponStaticMeshComponent->SetupAttachment(Cast<USceneComponent>(GetMesh()),"hand_lSocket");
	WeaponStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bDebugSpecificAttacak = false;
	SpecificAttackNumber = 0;
	bIsAttacking = false;
	CombatRange = 400.0f;
	OldAttackNumber = 0;
	JumpAttackRange = 1000.0f;
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

	WeaponStaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ABoss::CombatOnOverlapBegin);
	WeaponStaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &ABoss::CombatOnOverlapEnd);

	CombatTarget = Cast<AMainPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));

	BossAI = Cast<ABossAIController>(GetController());
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DistanceToCombatTarget = GetDistanceTo(Cast<AActor>(CombatTarget));

	/*if (!bIsAttacking && DistanceToCombatTarget <= CombatRange)
	{
		StartAttack();
	}*/
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

		int RandomAttackNumber = FMath::RandRange(0, 3);
		while (RandomAttackNumber == OldAttackNumber)
		{
			RandomAttackNumber = FMath::RandRange(0, 3);
		}

		if (bDebugSpecificAttacak)
		{
			RandomAttackNumber = SpecificAttackNumber;
		}

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ABoss::OnAnimationEnded);		
		AnimInstance->Montage_Play(CombatMontage);
		AnimInstance->Montage_SetEndDelegate(EndDelegate);

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
		default:
			AnimInstance->Montage_JumpToSection(TEXT("Combo01"));
			break;
		}

		bIsAttacking = true;
		OldAttackNumber = RandomAttackNumber;
	}
}

void ABoss::CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<AActor>(CombatTarget))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Player !!"));
	}
}

void ABoss::CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ABoss::OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
}

void ABoss::StartJumpAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CombatMontage)
	{
		if (AnimInstance->Montage_IsPlaying(CombatMontage))
		{
			return;
		}

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ABoss::OnAnimationEnded);
		AnimInstance->Montage_Play(CombatMontage);
		AnimInstance->Montage_SetEndDelegate(EndDelegate);
		AnimInstance->Montage_JumpToSection(TEXT("JumpAttack"));

		bIsAttacking = true;
	}
}