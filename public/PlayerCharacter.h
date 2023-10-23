// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API APlayerCharacter : public ARPGCharacter
{
	GENERATED_BODY()
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DefaultAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction7;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction8;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction9;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* QuickAction0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TargetLockAction;

	// Character Spawn Arrow with this Variable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AArrow> ArrowClass;

	UPROPERTY()
	class AArrow* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* FireAnimMontage;

	FVector FocalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDefaultScreenWidget> DefaultScreenClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UDefaultScreenWidget* DefaultScreen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Flag", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Flag", meta = (AllowPrivateAccess = "true"))
	bool bCombatting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Flag", meta = (AllowPrivateAccess = "true"))
	class AActor* TargetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UInventorySystem* Inventory;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UQuickSlotSystem* QuickSlotSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UQuestReceiver* QuestReceiver;

	UPROPERTY()
	FHitResult HitResult;

public:
	APlayerCharacter();

public:
	void RecoveryHp();

	void RecoveryMp();

	void GainXp();

	void TryInteraction();

	UDefaultScreenWidget* GetPlayerWidget() const { return DefaultScreen; }

	void StartCombat(class AActor* Opponent);

	FORCEINLINE class UStatComponent* GetStatComponent() const { return Stat; }

	FORCEINLINE class UInventorySystem* GetInventory() const { return Inventory; }

	FORCEINLINE class UQuickSlotSystem* GetQuickSlotSystem() const { return QuickSlotSystem; }

	FORCEINLINE class UQuestReceiver* GetQuestReceiver() const { return QuestReceiver; }

protected:
	void ReceivedAttackInput(const FInputActionValue& Value);

	FVector GetFocalPoint();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Tick(float DeltaTime) override;

	/*  */
	UFUNCTION()
	void EnemyDeath(FName Name);

private:
	UFUNCTION(BlueprintCallable)
	void SpawnArrow();

	void LineTraceForward();

	void SetTargetInfo();

	void ToggleInventory();

	void TargetLock();

	void PressKey1();

	void PressKey2();

	void PressKey3();

	void PressKey4();

	void PressKey5();

	void PressKey6();

	void PressKey7();

	void PressKey8();

	void PressKey9();

	void PressKey0();
};
