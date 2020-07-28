// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class ANIMATIONTEST_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class USphereComponent* CollectSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateSetting")
	float DegreePerSecond;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RotateSetting")
	FVector OriginPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateSetting")
	float SinFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateSetting")
	float SinAmplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateSetting")
	bool bShouldRotate;

	virtual void Pickup(class AMainPlayer* Player);
};
