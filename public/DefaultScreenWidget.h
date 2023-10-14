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
	class UImage* AimImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTargetInfoWidget* TargetInfo;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UInventoryWidget* InventoryWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UStorageWidget* Storage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UQuickSlotCollectionWidget* QuickSlot;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UDefaultStatWidget* DefaultStatWidget;

protected:
	virtual void NativeOnInitialized() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	void ActivateTargetInfo(class AActor* Opponent);

	void DeactivateTargetInfo();

	void LinkStorage(class UInventorySystem* StorageInventory);

	void ShowInventory();

	void HideInventory();

	void ToggleInventory();

	void ShowStorage();

	void HideStorage();

	void ToggleStorage();// 필요 없을듯
};
