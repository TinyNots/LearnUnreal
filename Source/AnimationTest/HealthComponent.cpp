// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.0f;
	Health = MaxHealth;
	OldHealth = 100.0f;
	HealthDecrementSpeed = 5.0f;
	HealthDelay = 1.0f;
	DelayCounter = 0.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OldHealth != Health)
	{
		if (DelayCounter < HealthDelay * 60.0f)
		{
			DelayCounter++;
		}
		else
		{
			//OldHealth -= HealthDecrementSpeed;

			OldHealth = UKismetMathLibrary::FInterpEaseInOut(OldHealth, Health, 0.1f, 2.0f);
			if (OldHealth <= Health)
			{
				OldHealth = Health;
				DelayCounter = 0.0f;
			}
		}
	}
}

