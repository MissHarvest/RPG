// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess))
	TSubclassOf<class UItemSlotWidget> ItemSlotClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget, AllowPrivateAccess))
	class UWrapBox* GridBox;

	UPROPERTY()
	TArray<class UItemSlotWidget*> ItemSlots;

	UPROPERTY()
	class UInventorySystem* InventoryModel;

public:
	void LinkInventory(class UInventorySystem* PlayerInventory);

private:
	UFUNCTION()
	void UpdatedInventory();
};
