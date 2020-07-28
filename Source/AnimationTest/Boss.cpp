// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "GameFramework/Controller.h"
#include "AIController.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABoss::ABoss()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponStaticMeshComponent->SetupAttachment(Cast<USceneComponent>(GetMesh()),"hand_lSocket");
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