// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainPlayer.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	CollectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectSphere"));
	CollectSphere->SetupAttachment(StaticMeshComponent);
	CollectSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	DegreePerSecond = 35.0f;
	SinFrequency = 1.0f;
	SinAmplitude = 0.5f;
	bShouldRotate = true;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	OriginPosition = GetActorLocation();

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollectSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	CollectSphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldRotate)
	{
		// Rotate the item around yaw axis with a certian amount of degree
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += DegreePerSecond * GetWorld()->GetDeltaSeconds();
		SetActorRotation(NewRotation);

		// Float the item with sin faction
		FVector NewLocation = GetActorLocation();
		NewLocation.Z += UKismetMathLibrary::Sin(UKismetSystemLibrary::GetGameTimeInSeconds(this) * UKismetMathLibrary::GetPI() * SinFrequency) * SinAmplitude;
		SetActorLocation(NewLocation);
	}
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (Player)
	{
		Player->SetSelectedItem(this);
	}
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainPlayer* Player = Cast<AMainPlayer>(OtherActor);
	if (Player && Player->GetSelectedItem() == this)
	{
		Player->SetSelectedItem(nullptr);
	}
}

void AItem::Pickup(AMainPlayer* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("You should not use this pickup function !"));
	Player->SetSelectedItem(nullptr);
	Destroy();
}