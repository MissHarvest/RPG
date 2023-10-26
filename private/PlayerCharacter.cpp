// Fill out your copyright notice in the Description page of Project Settings.

// Player
#include "PlayerCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/PlayerController.h>
#include "StatComponent.h"
#include "InventorySystem.h"
#include "PlayerCameraComponent.h"
#include "QuickSlotSystem.h"
#include "QuestReceiver.h"
#include <Components/CapsuleComponent.h>

// Other Class
#include "Arrow.h"
#include "DefaultScreenWidget.h"
#include "InventoryWidget.h"
#include "Recovery.h"
#include "ItemBase.h"
#include "InteractionInterface.h"
#include "EnemyCharacter.h"
#include "QuestGiverWidget.h"

// Unreal System
#include "EnhancedInputComponent.h"
#include <Blueprint/UserWidget.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

// Kismet System
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/KismetSystemLibrary.h>

APlayerCharacter::APlayerCharacter()
{
	// Components Init Settting
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -96.0f), FRotator(0, -90, 0));

	GetCharacterMovement()->GravityScale = 1.75f;

	GetCameraBoom()->SetRelativeLocation(FVector(0, 0, 125));
	GetCameraBoom()->TargetArmLength = 700.0f;

	Stat = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));
	Inventory = CreateDefaultSubobject<UInventorySystem>(TEXT("Inventory"));
	QuickSlotSystem = CreateDefaultSubobject<UQuickSlotSystem>(TEXT("Quick Slot System"));
	QuestReceiver = CreateDefaultSubobject<UQuestReceiver>(TEXT("Quest Receiver"));

	PID = "000001";
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
			DefaultScreen->AddToViewport();
		}
	}
	
	Stat->DecreaseHP(50);
	
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::CloseWidget);

	/* Inventory System Link QuickSlotSystem */
	Inventory->QuickSlotSystem = QuickSlotSystem;
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Attack
		EnhancedInputComponent->BindAction(DefaultAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ReceivedAttackInput);

		// Quick Slot
		EnhancedInputComponent->BindAction(QuickAction1, ETriggerEvent::Started, this, &APlayerCharacter::PressKey1);
		EnhancedInputComponent->BindAction(QuickAction2, ETriggerEvent::Started, this, &APlayerCharacter::PressKey2);
		EnhancedInputComponent->BindAction(QuickAction3, ETriggerEvent::Started, this, &APlayerCharacter::PressKey3);
		EnhancedInputComponent->BindAction(QuickAction4, ETriggerEvent::Started, this, &APlayerCharacter::PressKey4);
		EnhancedInputComponent->BindAction(QuickAction5, ETriggerEvent::Started, this, &APlayerCharacter::PressKey5);
		EnhancedInputComponent->BindAction(QuickAction6, ETriggerEvent::Started, this, &APlayerCharacter::PressKey6);
		EnhancedInputComponent->BindAction(QuickAction7, ETriggerEvent::Started, this, &APlayerCharacter::PressKey7);
		EnhancedInputComponent->BindAction(QuickAction8, ETriggerEvent::Started, this, &APlayerCharacter::PressKey8);
		EnhancedInputComponent->BindAction(QuickAction9, ETriggerEvent::Started, this, &APlayerCharacter::PressKey9);
		EnhancedInputComponent->BindAction(QuickAction0, ETriggerEvent::Started, this, &APlayerCharacter::PressKey0);		
		

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::TryInteraction);

		// On Off Inventory
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &APlayerCharacter::ToggleInventory);

		// Target Lock
		EnhancedInputComponent->BindAction(TargetLockAction, ETriggerEvent::Started, this, &APlayerCharacter::TargetLock);
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
	Cast<UPlayerCameraComponent>(Camera)->FindEnemyAtForward(HitResult);
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
	// Tag 가 아닌 Cast 으로 구분하는 것은  ? 
	if (HitResult.bBlockingHit && HitResult.GetActor()->ActorHasTag(FName(TEXT("Enemy"))) || bCombatting)
	{
		DefaultScreen->ActivateTargetInfo(HitResult.GetActor());
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

void APlayerCharacter::TryInteraction()
{
	TArray<AActor*> OverlapActors;
	GetOverlappingActors(OverlapActors, AActor::StaticClass());
	if (OverlapActors.Num() <= 0) return;
	if (!UKismetSystemLibrary::DoesImplementInterface(OverlapActors[0], UInteractionInterface::StaticClass())) return;

	if (OverlapActors[0]->ActorHasTag(TEXT("Interaction")))
	{
		auto Interaction = Cast<IInteractionInterface>(OverlapActors[0]);
		Interaction->Interact();
	}
	else if (OverlapActors[0]->ActorHasTag(TEXT("QuestGiver")))
	{
		auto Interaction = Cast<IInteractionInterface>(OverlapActors[0]);
		ShowQuestGiverWidget(Interaction->ReceiveQuest(QuestReceiver));
	}
	else if (OverlapActors[0]->ActorHasTag(TEXT("Item")))
	{
		auto Item = Cast<AItemBase>(OverlapActors[0]);

		if (Inventory->AddItem(Item->GetItem())) /* Get Item Info */
			Item->Destroy();
	}
}

void APlayerCharacter::ToggleInventory()
{
	DefaultScreen->ToggleInventory();
}

void APlayerCharacter::StartCombat(class AActor* Opponent)
{
	bCombatting = true;
	DefaultScreen->ActivateTargetInfo(Opponent);
}

void APlayerCharacter::TargetLock()
{
	Cast<UPlayerCameraComponent>(GetFollowCamera())->SetTargetToChase();
}

void APlayerCharacter::PressKey1()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey1);
}

void APlayerCharacter::PressKey2()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey2);
}

void APlayerCharacter::PressKey3()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey3);
}

void APlayerCharacter::PressKey4()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey4);
}

void APlayerCharacter::PressKey5()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey5);
}

void APlayerCharacter::PressKey6()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey6);
}

void APlayerCharacter::PressKey7()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey7);
}

void APlayerCharacter::PressKey8()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey8);
}

void APlayerCharacter::PressKey9()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey9);
}

void APlayerCharacter::PressKey0()
{
	QuickSlotSystem->Press(EQuickSlotKey::NumberKey0);
}

void APlayerCharacter::EnemyDeath(FName Name)
{
	QuestReceiver->UpdateQuestProgress(Name);
}

void APlayerCharacter::ShowQuestGiverWidget(TArray<FString> ListQID)
{
	if (QuestPanelWidgetClass)
	{
		QuestGiverWidget = CreateWidget<UQuestGiverWidget>(Cast<APlayerController>(Controller), QuestPanelWidgetClass);

		if (QuestGiverWidget)
		{
			auto PlayerController = Cast<APlayerController>(Controller);
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, QuestGiverWidget);
			PlayerController->SetShowMouseCursor(true);

			QuestGiverWidget->AddQuest(QuestReceiver->GetPerformableQuest(ListQID)); // add - > show ?
			QuestGiverWidget->SetReceiver(QuestReceiver);
			QuestGiverWidget->AddToViewport();
		}
	}
}

void APlayerCharacter::CloseWidget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (QuestGiverWidget)
	{
		auto PlayerController = Cast<APlayerController>(Controller);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->SetShowMouseCursor(false);
		QuestGiverWidget->RemoveFromParent();
		QuestGiverWidget = nullptr;
	}
}