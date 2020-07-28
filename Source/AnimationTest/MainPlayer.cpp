// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon.h"
#include "Item.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 600.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	bUseControllerRotationYaw = false;

	WalkToMaxTime = 1.5f;
	DefaultWalkSpeed = 550.0f;
	DefaultMaxWalkSpeed = 800.0f;

	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	GetCharacterMovement()->GroundFriction = 10.0f;
	bIsRunning = false;
	bIsTargetLock = false;
	bIsRolling = false;

	MaxDegreePerSecond = 720.0f;
	MaxPossibleRotation = 180.0f;

	bTurnToLockTarget = false;
	CameraInterpSpeed = 360.0f;
	StepBackPower = 12.5f;

	bIsBackStep = false;
	CoolDownTime = 0.05f;
	CoolDownCounter = 0.0f;
	bShouldCoolDown = false;
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		if (CameraManager)
		{
			CameraManager->ViewPitchMin = -45.0f;
			CameraManager->ViewPitchMax = 45.0f;
		}
	}

	AnimInstance = GetMesh()->GetAnimInstance();
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsRunning && !bIsTargetLock)
	{
		VelocitySystem(WalkToMaxTime);
	}

	if (bIsTargetLock)
	{
		if (bIsRolling)
		{
			return;
		}

		GetCharacterMovement()->bOrientRotationToMovement = false;

		FRotator NewRotation = UKismetMathLibrary::RInterpTo(
			GetActorRotation(),
			UKismetMathLibrary::MakeRotFromX(CameraComponent->GetForwardVector()),
			GetWorld()->GetDeltaSeconds(),
			CameraInterpSpeed * GetWorld()->GetDeltaSeconds());

		SetActorRotation(FRotator(GetActorRotation().Pitch, NewRotation.Yaw, GetActorRotation().Roll));
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	if (bIsBackStep)
	{
		SetActorLocation(GetActorLocation() + -GetActorForwardVector() * StepBackPower);
	}

	if (bShouldCoolDown)
	{
		if (CoolDownCounter <= CoolDownTime * 60.0f)
		{
			CoolDownCounter++;
		}
		else
		{
			bShouldCoolDown = false;
			CoolDownCounter = 0.0f;
		}

	}
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("ForwardAxis", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("SideAxis", this, &AMainPlayer::MoveSide);

	PlayerInputComponent->BindAxis("Turn", this, &AMainPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainPlayer::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AMainPlayer::SprintStart);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AMainPlayer::SprintEnd);

	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &AMainPlayer::RollStart);
	PlayerInputComponent->BindAction("Pickup", EInputEvent::IE_Pressed, this, &AMainPlayer::UsePickupItem);
}

void AMainPlayer::MoveForward(float Value)
{
	if (!bIsBackStep)
	{
		AddMovementInput(CameraComponent->GetForwardVector(), Value);
	}
}

void AMainPlayer::MoveSide(float Value)
{
	if (!bIsBackStep)
	{
		AddMovementInput(CameraComponent->GetRightVector(), Value);
	}
}

void AMainPlayer::SprintStart()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed;
}

void AMainPlayer::SprintEnd()
{
	bIsRunning = false;
}

void AMainPlayer::RollStart()
{
	if (bIsRolling || bIsBackStep || bShouldCoolDown)
	{
		return;
	}

	bTurnToLockTarget = false;
	
	if (CombatMontage && !AnimInstance->Montage_IsPlaying(CombatMontage))
	{
		AnimInstance->Montage_Play(CombatMontage);
		if (GetLastMovementInputVector() != FVector::ZeroVector)
		{
			bIsRolling = true;
			AnimInstance->Montage_JumpToSection("Roll");
		}
		else
		{
			bIsBackStep = true;
			AnimInstance->Montage_JumpToSection("StepBack");
		}
	}
}

void AMainPlayer::RollEnd()
{
	if (bIsBackStep)
	{
		bShouldCoolDown = true;
	}

	bIsRolling = false;
	bIsBackStep = false;
}

void AMainPlayer::VelocitySystem(float Time)
{
	float SpeedDecreaseRate = (DefaultMaxWalkSpeed - DefaultWalkSpeed) / (60.0f / Time);

	GetCharacterMovement()->MaxWalkSpeed -= SpeedDecreaseRate;
	GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(GetCharacterMovement()->MaxWalkSpeed, DefaultWalkSpeed, DefaultMaxWalkSpeed);
}

FRotator AMainPlayer::GetDesiredRotation()
{
	if (GetLastMovementInputVector() != FVector::ZeroVector)
	{
		return UKismetMathLibrary::MakeRotFromX(GetLastMovementInputVector());;
	}
	else
	{
		return GetActorRotation();
	}

	UE_LOG(LogTemp, Error, TEXT("Did not return the desired rotation"));
	return FRotator::ZeroRotator;
}

void AMainPlayer::SetWeapon(AWeapon* NewWeapon)
{
	EquippedWeapon = NewWeapon;
}

AWeapon* AMainPlayer::GetWeapon()
{
	return EquippedWeapon;
}

void AMainPlayer::SetSelectedItem(AItem* NewItem)
{
	SeletectedItem = NewItem;
}

AItem* AMainPlayer::GetSelectedItem()
{
	return SeletectedItem;
}

void AMainPlayer::UsePickupItem()
{
	if (SeletectedItem)
	{
		SeletectedItem->Pickup(this);
	}
}

void AMainPlayer::SetShield(AShield* NewShield)
{
	EquippedShield = NewShield;
}

AShield* AMainPlayer::GetShield()
{
	return EquippedShield;
}
