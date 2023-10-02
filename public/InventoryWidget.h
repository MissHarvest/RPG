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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemSlotWidget> ItemSlotClass;

	UPROPERTY()
	TArray<class UItemSlotWidget*> ItemSlots; // smart pointer 를 사용해야 할까?

	UPROPERTY()
	class UInventorySystem* InventoryModel;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* GridBox;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void UpdatedInventory();

	void CreateItemSlots();	
};
