// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotCollectionWidget.h"
#include "QuickSlotSystem.h"
#include "QuickSlotWidget.h"

void UQuickSlotCollectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UQuickSlotCollectionWidget::LinkQuickSlot(class UQuickSlotSystem* QuickSlot)
{
	if (IsValid(QuickSlot)) return;

	// Bind
	QuickSlot->OnQuickSlotChanged.AddDynamic(this, &UQuickSlotCollectionWidget::UpdateQuickSlots);

	//
	QuickSlotModel = QuickSlot;

	for (int i = 0; i < 1; ++i)
	{
		//QuickSlots[i]->SetQuickSlotModel(PlayerInventory);
	}
}

void UQuickSlotCollectionWidget::UpdateQuickSlots()
{
	for (int i = 0; i < QuickSlots.Num(); ++i)
	{
		QuickSlots[i]->SetQuickSlot(QuickSlotModel->QuickSlots[i]);
	}
}