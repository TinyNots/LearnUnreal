// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UActorSpawner.generated.h"

UCLASS()
class ANIMATIONTEST_API AUActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ActorSpawner")
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActorSpawner")
	AActor* ActorTracker;

public:	

	void SpawnActor();

private:

	bool IsActorClassSet();

	bool IsTrackingActorAlive();
};
