// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/WrapBox.h"
#include "ItemSlotWidget.h"
#include "InventorySystem.h"

// OnInit : Set Padding?

void UInventoryWidget::LinkInventory(class UInventorySystem* PlayerInventory)
{
	// Bind
	PlayerInventory->OnSlotChanged.AddDynamic(this, &UInventoryWidget::UpdatedInventory);

	//
	InventoryModel = PlayerInventory;

	//
	int32 Size = PlayerInventory->GetSize();
	UE_LOG(LogTemp, Warning, TEXT("Size : %d"), Size);
	for (int i = 0; i < Size; ++i)
	{
		auto ItemSlot = CreateWidget<UItemSlotWidget>(GetOwningPlayer(), ItemSlotClass);
		ItemSlot->SetInventoryModel(PlayerInventory);
		ItemSlot->SetIndex(i);
		GridBox->AddChild(ItemSlot);
		ItemSlots.Add(ItemSlot);
	}
}

void UInventoryWidget::UpdatedInventory()
{
	for (int i = 0; i < InventoryModel->GetSize(); ++i)
	{
		ItemSlots[i]->SetItem(InventoryModel->GetContent(i));
	}
}