// Fill out your copyright notice in the Description page of Project Settings.


#include "PFSpawnerManager.h"
#include "UActorSpawner.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

#if !UE_BUILD_SHIPPING
#include "Engine/GameEngine.h"
#include "DrawDebugHelpers.h"
#endif

// Sets default values
APFSpawnerManager::APFSpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsDebugMode = false;
	DistanceToSpawn = 500.0f;
}

// Called when the game starts or when spawned
void APFSpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	FindAllSpawner();

	TargetCharacter = UGameplayStatics::GetPlayerCharacter((UObject*)GetWorld(), 0);
	if (!TargetCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("No target was choosen."));
	}

	// Spawn all actor for the first time
	for (const auto & Spawner : Spawners)
	{
		Spawner->SpawnActor();
	}
}

// Called every frame
void APFSpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnActorWithDistance();
}

void APFSpawnerManager::FindAllSpawner()
{
	if (SpawnerClass)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass((UObject*)GetWorld(), AUActorSpawner::StaticClass(), FoundActors);

		if (FoundActors.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No actor was found"));
			return;
		}

		Spawners.Reserve(FoundActors.Num());
		for (const auto & FoundActor : FoundActors)
		{
			Spawners.Add(Cast<AUActorSpawner>(FoundActor));
		}
	}
}

void APFSpawnerManager::SpawnActorWithDistance()
{
	for (const auto & Spawner : Spawners)
	{
		auto DistanceSpawnerToTarget = FVector::Distance(Spawner->GetActorLocation(), TargetCharacter->GetActorLocation());

#if !UE_BUILD_SHIPPING

		if (bIsDebugMode)
		{
			FString DebugMessage = FString::Printf(TEXT("Distance = %f"), DistanceSpawnerToTarget);
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, DebugMessage);
			DrawDebugLine(GetWorld(), Spawner->GetActorLocation(), TargetCharacter->GetActorLocation(), FColor::Green, false, -1.0f, (uint8)'\000', 2.0f);
		}

#endif

		if (DistanceSpawnerToTarget >= DistanceToSpawn)
		{
			Spawner->SpawnActor();
		}
	}
}

