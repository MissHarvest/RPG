// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UStorageWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemSlotWidget> ItemSlotClass;

	UPROPERTY()
	TArray<class UItemSlotWidget*> ItemSlots;

	UPROPERTY()
	class UInventorySystem* InventoryModel;

	UPROPERTY()
	int32 Size;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* GridBox;

public:
	void LinkInventory(class UInventorySystem* PlayerInventory);

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void UpdatedInventory();

	void CreateItemSlots();
};
