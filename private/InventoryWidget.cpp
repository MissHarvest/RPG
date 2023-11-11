// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/WrapBox.h"
#include "ItemSlotWidget.h"
#include "InventorySystem.h"
#include <Components/PanelWidget.h>
#include "PlayerCharacter.h"

// OnInit : Set Padding?
void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	// invnetorymodel var to change local var //
	InventoryModel = Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetInventory();
	if (nullptr == InventoryModel) return;

	InventoryModel->OnSlotChanged.AddDynamic(this, &UInventoryWidget::UpdatedInventory);

	/* BroadCast */

	CreateItemSlots();
}

void UInventoryWidget::UpdatedInventory(int32 Index, FItemSlot ItemSlot)
{
	ItemSlots[Index]->SetItem(ItemSlot);
}

void UInventoryWidget::CreateItemSlots()
{
	for (int i = 0; i < InventoryModel->GetSize(); ++i)
	{
		auto ItemSlot = CreateWidget<UItemSlotWidget>(GetOwningPlayer(), ItemSlotClass);
		ItemSlot->SetIndex(i);
		ItemSlot->SetInventoryModel(InventoryModel);
		GridBox->AddChild(ItemSlot);
		ItemSlots.Add(ItemSlot);
	}
}