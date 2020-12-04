// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/BoxComponent.h"
#include "MainPlayer.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

AWeapon::AWeapon()
{
	CombatBox = CreateDefaultSubobject<UBoxComponent>("CombatBox");
	CombatBox->SetupAttachment(GetRootComponent());
	CombatBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CombatBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapBegin);
	CombatBox->OnComponentEndOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapEnd);

	if (!AnimationMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon Animation Montage is empty. Please insert the assert."));
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeapon::CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWeapon::EquipWeapon(AMainPlayer* Player)
{
	// Check if the player has weapon then detach from player and exchange places with this weapon
	AWeapon* OldWeapon = Player->GetWeapon();
	if (OldWeapon)
	{
		OldWeapon->bShouldRotate = true;
		OldWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		OldWeapon->SetActorTransform(this->GetActorTransform());
		OldWeapon->CollectSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	// Get socket from player and attach this weapon to the player
	const USkeletalMeshSocket* HandSocket = Player->GetMesh()->GetSocketByName("RightWeaponShield");
	if (HandSocket)
	{
		bShouldRotate = false;
		HandSocket->AttachActor(this, Player->GetMesh());
		CombatBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CollectSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Player->SetWeapon(this);

		// Set the weapon to the correct position spot
		SetActorRelativeLocation(FVector(6.0f, 2.0f, 0.0f));
	}
}

void AWeapon::Pickup(AMainPlayer* Player)
{
	EquipWeapon(Player);
	if (!Player->GetWeapon())
	{
		Player->SetSelectedItem(nullptr);
	}
}

UAnimMontage* AWeapon::GetAnimationMontage()
{
	return AnimationMontage;
}
