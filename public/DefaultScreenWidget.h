// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DefaultScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UDefaultScreenWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UProgressBar* HpBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UProgressBar* MpBar;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UProgressBar* XpBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* LvText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UImage* AimImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTargetInfoWidget* TargetInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UInventoryWidget* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"))
	class UInventoryWidget* Storage;

public: // public? private?
	UFUNCTION()
	void SetHpPercent(float Percent);

	UFUNCTION()
	void SetMpPercent(float Percent);

	UFUNCTION()
	void SetXpPercent(float Percent);

public:
	void LinkStatController(class UStatComponent* StatComponent);

	void ActivateTargetInfo(class AActor* Opponent);

	void DeactivateTargetInfo();

	void LinkInventory(class UInventorySystem* PlayerInventory);

	void LinkStorage(class UInventorySystem* StorageInventory);

	void ShowInventory();

	void HideInventory();

	void ToggleInventory();

	void ShowStorage();

	void HideStorage();

	void ToggleStorage();// 필요 없을듯
};
