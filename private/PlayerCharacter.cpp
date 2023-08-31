// Fill out your copyright notice in the Description page of Project Settings.

// Player
#include "PlayerCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/PlayerController.h>
#include "StatComponent.h"

// Other Class
#include "Arrow.h"
#include "DefaultScreenWidget.h"
#include "Recovery.h"

// Unreal System
#include "EnhancedInputComponent.h"
#include <Blueprint/UserWidget.h>

// Kismet System
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

APlayerCharacter::APlayerCharacter()
{
	// Components Init Settting
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -96.0f), FRotator(0, -90, 0));

	GetCharacterMovement()->GravityScale = 1.75f;

	GetCameraBoom()->SetRelativeLocation(FVector(0, 0, 125));
	GetCameraBoom()->TargetArmLength = 700.0f;

	Stat = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(DefaultScreenClass))
	{
		DefaultScreen = CreateWidget<UDefaultScreenWidget>(Cast<APlayerController>(Controller), DefaultScreenClass);
		DefaultScreen->LinkStatController(Stat);
		DefaultScreen->AddToViewport();
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(DefaultAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ReceivedAttackInput);

		// Quick Slot
		EnhancedInputComponent->BindAction(QuickAction, ETriggerEvent::Started, this, &APlayerCharacter::RecoveryHp);
	}
}

void APlayerCharacter::ReceivedAttackInput(const FInputActionValue& Value)
{
	if (bIsAttacking) return;
	bIsAttacking = true;

	if (IsValid(FireAnimMontage))
		PlayAnimMontage(FireAnimMontage, 1.0f, FName("Play"));
	
	FocalLocation = GetFocalPoint();
	FVector lookDirection = FocalLocation - GetActorLocation();
	lookDirection.Z = 0;
	SetActorRotation(UKismetMathLibrary::MakeRotFromX(lookDirection));
}

FVector APlayerCharacter::GetFocalPoint()
{
	FHitResult HitResult;
	auto Camera = GetFollowCamera();
	FVector StartPoint = Camera->K2_GetComponentLocation();
	FVector FocalPoint = StartPoint + Camera->GetForwardVector() * 15000.0f;
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, FocalPoint, ECollisionChannel::ECC_Visibility);
	if (IsHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *(HitResult.GetActor()->GetName()));
		return HitResult.ImpactPoint; 
	}
	return FocalPoint;
}

void APlayerCharacter::SpawnArrow()
{
	if (IsValid(ArrowClass))
	{
		auto SpawnLocation = GetMesh()->GetSocketLocation("bow_SpawnSocket");
		auto SpawnRotation = UKismetMathLibrary::MakeRotFromX(FocalLocation - SpawnLocation);
		FActorSpawnParameters params;
		params.Owner = this;
		GetWorld()->SpawnActor<AArrow>(ArrowClass, SpawnLocation, SpawnRotation, params);
	}
}

void APlayerCharacter::RecoveryHp()
{
	//Stat->RecoveryHp(10, 3);// NewObejct<NormalRecovery>();
	Stat->RecoveryHp(10, NewObject<UNormalRecovery>());
}