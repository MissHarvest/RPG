// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageWidget.h"
#include "InventorySystem.h"
#include "ItemSlotWidget.h"
#include <Components/WrapBox.h>

void UStorageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Size = 20;
	CreateItemSlots();
}

void UStorageWidget::LinkInventory(class UInventorySystem* PlayerInventory)
{
	if (IsValid(InventoryModel)) return;

	// Bind
	PlayerInventory->OnSlotChanged.AddDynamic(this, &UStorageWidget::UpdatedInventory);

	//
	InventoryModel = PlayerInventory;

	for (int i = 0; i < Size; ++i)
	{
		ItemSlots[i]->SetInventoryModel(PlayerInventory);
	}
}

void UStorageWidget::UpdatedInventory(int32 Index, FItemSlot ItemSlot)
{
	ItemSlots[Index]->SetItem(ItemSlot);
}

void UStorageWidget::CreateItemSlots()
{
	for (int i = 0; i < Size; ++i)
	{
		auto ItemSlot = CreateWidget<UItemSlotWidget>(GetOwningPlayer(), ItemSlotClass);
		ItemSlot->SetIndex(i);
		GridBox->AddChild(ItemSlot);
		ItemSlots.Add(ItemSlot);
	}
}