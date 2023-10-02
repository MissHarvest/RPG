// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotCollectionWidget.h"
#include "QuickSlotSystem.h"
#include "QuickSlotWidget.h"
#include "Components/WrapBox.h"
#include "PlayerCharacter.h"

void UQuickSlotCollectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	QuickSlotKeyNameCollection = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

	QuickSlotModel = Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetQuickSlotSystem();
	if (nullptr == QuickSlotModel) return;

	QuickSlotModel->OnQuickSlotChanged.AddDynamic(this, &UQuickSlotCollectionWidget::UpdateQuickSlots);
	
	CreateQuickSlots();
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
	for (int i = 0; i < QuickSlotModel->GetSize(); ++i)
	{
		auto QuickSlot = CreateWidget<UQuickSlotWidget>(GetOwningPlayer(), QuickSlotClass);
		QuickSlot->SetQuickSlotModel(QuickSlotModel);
		QuickSlot->SetIndex(i);
		QuickSlot->SetKeyName(QuickSlotKeyNameCollection[i]);
		QuickSlotWidgets.Add(QuickSlot);		
		QuickSlotGridBox->AddChild(QuickSlot);
	}
}