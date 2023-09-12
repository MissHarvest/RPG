// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/WrapBox.h"
#include "ItemSlotWidget.h"
#include "InventorySystem.h"

// OnInit : Set Padding?
void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Size = 20;
	CreateItemSlots();
}

void UInventoryWidget::LinkInventory(class UInventorySystem* PlayerInventory)
{
	if (IsValid(InventoryModel)) return;
	
	// Bind
	PlayerInventory->OnSlotChanged.AddDynamic(this, &UInventoryWidget::UpdatedInventory);

	//
	InventoryModel = PlayerInventory;

	for (int i = 0; i < Size; ++i)
	{
		ItemSlots[i]->SetInventoryModel(PlayerInventory);
	}
}

void UInventoryWidget::UpdatedInventory()
{
	for (int i = 0; i < InventoryModel->GetSize(); ++i)
	{
		ItemSlots[i]->SetItem(InventoryModel->GetContent(i));
	}
}

void UInventoryWidget::CreateItemSlots()
{
	for (int i = 0; i < Size; ++i)
	{
		auto ItemSlot = CreateWidget<UItemSlotWidget>(GetOwningPlayer(), ItemSlotClass);
		ItemSlot->SetIndex(i);
		GridBox->AddChild(ItemSlot);
		ItemSlots.Add(ItemSlot);
	}
}