// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"
#include "Components/BoxComponent.h"
#include "MainPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"

AShield::AShield()
{
	DefendBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DefendBox"));
	DefendBox->SetupAttachment(GetRootComponent());
	DefendBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AShield::BeginPlay()
{
	Super::BeginPlay();

	DefendBox->OnComponentBeginOverlap.AddDynamic(this, &AShield::DefendOnOverlapBegin);
	DefendBox->OnComponentEndOverlap.AddDynamic(this, &AShield::DefendOnOverlapEnd);
}

void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShield::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AShield::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AShield::Pickup(AMainPlayer* Player)
{
	EquipShield(Player);
	if (!Player->GetShield())
	{
		Player->SetSelectedItem(nullptr);
	}
}

void AShield::EquipShield(AMainPlayer* Player)
{
	// Check if the player has shield then detach from player and exchange places with this shield
	AShield* OldShield = Player->GetShield();
	if (OldShield)
	{
		OldShield->bShouldRotate = true;
		OldShield->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		OldShield->SetActorTransform(this->GetActorTransform());
		OldShield->CollectSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	// Get socket from player and attach this shield to the player
	const USkeletalMeshSocket* HandSocket = Player->GetMesh()->GetSocketByName("LeftWeaponShield");
	if (HandSocket)
	{
		bShouldRotate = false;
		HandSocket->AttachActor(this, Player->GetMesh());
		DefendBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CollectSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Player->SetShield(this);

		// Set the shield to the correct position and rotation
		SetActorRelativeLocation(FVector(-1.0f, 5.0f, 3.0f));
		SetActorRelativeRotation(FRotator(0.0f, -20.0f, 0.0f));
	}
}

void AShield::DefendOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AShield::DefendOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
