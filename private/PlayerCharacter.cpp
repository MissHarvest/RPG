// Fill out your copyright notice in the Description page of Project Settings.

// Player
#include "PlayerCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/PlayerController.h>
#include "StatComponent.h"
#include "InventorySystem.h"

// Other Class
#include "Arrow.h"
#include "DefaultScreenWidget.h"
#include "Recovery.h"
#include "ItemBase.h"

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
	Inventory = CreateDefaultSubobject<UInventorySystem>(TEXT("Inventory"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player BeginPlay"));
	if (IsValid(DefaultScreenClass))
	{
		DefaultScreen = CreateWidget<UDefaultScreenWidget>(Cast<APlayerController>(Controller), DefaultScreenClass);
		if (IsValid(DefaultScreen))
		{
			DefaultScreen->LinkStatController(Stat);
			DefaultScreen->LinkInventory(Inventory);
			DefaultScreen->AddToViewport();			
		}
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
		EnhancedInputComponent->BindAction(QuickAction1, ETriggerEvent::Started, this, &APlayerCharacter::RecoveryHp);
		EnhancedInputComponent->BindAction(QuickAction2, ETriggerEvent::Started, this, &APlayerCharacter::RecoveryMp);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::LootItem);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	LineTraceForward();

	SetTargetInfo();
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

void APlayerCharacter::LineTraceForward()
{
	auto Camera = GetFollowCamera();
	FVector StartPoint = Camera->K2_GetComponentLocation();
	FVector FocalPoint = StartPoint + Camera->GetForwardVector() * 15000.0f;
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, FocalPoint, ECollisionChannel::ECC_Visibility);
}

FVector APlayerCharacter::GetFocalPoint()
{
	if (HitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *(HitResult.GetActor()->GetName()));
		return HitResult.ImpactPoint; 
	}
	return HitResult.TraceEnd;
}

void APlayerCharacter::SetTargetInfo()
{
	if (HitResult.bBlockingHit && HitResult.GetActor()->ActorHasTag(FName(TEXT("Enemy"))))
	{
		DefaultScreen->ActivateTargetInfo();
	}
	else
	{
		DefaultScreen->DeactivateTargetInfo();
	}
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
	Stat->RecoveryHp(10);
	// Stat->RecoveryHp(10, 3);
}

void APlayerCharacter::RecoveryMp()
{
	UE_LOG(LogTemp, Warning, TEXT("MP. %s"), *(this->GetName()));
	Stat->RecoveryMp(10);
}

void APlayerCharacter::GainXp()
{
	Stat->GainXp(10);
}

void APlayerCharacter::LootItem()
{
	TArray<AActor*> OverlapActors;
	GetOverlappingActors(OverlapActors, AItemBase::StaticClass());
	if (OverlapActors.Num() > 0)
	{
		auto Item = Cast<AItemBase>(OverlapActors[0]);
		if(Inventory->AddItem(Item->GetItemSlot()))
			Item->Destroy();
	}
}