// Fill out your copyright notice in the Description page of Project Settings.


#include "UActorSpawner.h"
#include "Engine/World.h"

// Sets default values
AUActorSpawner::AUActorSpawner()
{
}

// Called when the game starts or when spawned
void AUActorSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AUActorSpawner::SpawnActor()
{
	if (!IsActorClassSet() || IsTrackingActorAlive())
	{
		return;
	}

	UWorld* WorldReference = GetWorld();
	if (WorldReference)
	{
		ActorTracker = WorldReference->SpawnActor<AActor>(ActorClass, GetActorTransform());
	}
}

bool AUActorSpawner::IsTrackingActorAlive()
{
	return ActorTracker != nullptr ? true : false;
}

bool AUActorSpawner::IsActorClassSet()
{
	if (!ActorClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor to spawn is null."));
		return false;
	}
	return true;
}
