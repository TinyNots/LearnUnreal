// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFSpawnerManager.generated.h"

class AUActorSpawner;
class ACharacter;

UCLASS()
class ANIMATIONTEST_API APFSpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFSpawnerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "PFSpawnerManager")
	ACharacter* TargetCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PFSpawnerManager")
	TSubclassOf<AUActorSpawner> SpawnerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PFSpawnerManager")
	float DistanceToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PFSpawner Manager | Debug")
	bool bIsDebugMode;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	TArray<AUActorSpawner*> Spawners;

	void FindAllSpawner();

	void SpawnActorWithDistance();

};
