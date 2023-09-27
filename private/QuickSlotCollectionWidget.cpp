// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotCollectionWidget.h"
#include "QuickSlotSystem.h"
#include "QuickSlotWidget.h"
#include "Components/WrapBox.h"

void UQuickSlotCollectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Size = 10;
	CreateQuickSlots();
}

void UQuickSlotCollectionWidget::LinkQuickSlot(class UQuickSlotSystem* QuickSlot)
{
	if (nullptr == QuickSlot) return;
	
	// Bind
	QuickSlot->OnQuickSlotChanged.AddDynamic(this, &UQuickSlotCollectionWidget::UpdateQuickSlots);

	//
	QuickSlotModel = QuickSlot;

	for (int i = 0; i < 10; ++i)
	{
		QuickSlotWidgets[i]->SetQuickSlotModel(QuickSlotModel);
	}
}

void UQuickSlotCollectionWidget::UpdateQuickSlots()
{
	for (int i = 0; i < QuickSlotWidgets.Num(); ++i)
	{
		QuickSlotWidgets[i]->SetQuickSlot(QuickSlotModel->QuickSlots[i]);
	}
}

void UQuickSlotCollectionWidget::CreateQuickSlots()
{
	for (int i = 0; i < Size; ++i)
	{
		auto QuickSlot = CreateWidget<UQuickSlotWidget>(GetOwningPlayer(), QuickSlotClass);
		QuickSlot->SetIndex(i);
		QuickSlotWidgets.Add(QuickSlot);
		GridBox->AddChild(QuickSlot);
	}
}