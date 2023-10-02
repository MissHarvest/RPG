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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* MpBar;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* XpBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LvText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* AimImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTargetInfoWidget* TargetInfo;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UInventoryWidget* InventoryWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UStorageWidget* Storage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UQuickSlotCollectionWidget* QuickSlot;

public: // public? private?
	UFUNCTION()
	void SetHpPercent(float Percent);

	UFUNCTION()
	void SetMpPercent(float Percent);

	UFUNCTION()
	void SetXpPercent(float Percent);

protected:
	virtual void NativeOnInitialized() override;

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

	void LinkQuickSlot(class UQuickSlotSystem* PlayerQuickSlot);
};
