// Fill out your copyright notice in the Description page of Project Settings.

// DefaultScreen
#include "DefaultScreenWidget.h"

// Widget
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "TargetInfoWidget.h"
#include "InventoryWidget.h"
#include "QuickSlotCollectionWidget.h"
#include "StorageWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"

// Other Class
#include "StatComponent.h"

#include "PlayerCharacter.h"
//
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>

#include "QuickSlotSystem.h"
#include "QuickSlotDragDropOperation.h"

void UDefaultScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(LogTemp, Warning, TEXT("Default Screen Widget _ Native On Init"));
}

bool UDefaultScreenWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Default Game Native On Drop"));
	auto QuickOperation = Cast<UQuickSlotDragDropOperation>(InOperation);
	if (QuickOperation)
	{
		QuickOperation->GetSystem()->ClearQuickSlotByIndex(QuickOperation->GetIndex());
		return true;
	}
	return false;

}

void UDefaultScreenWidget::ActivateTargetInfo(class AActor* Opponent)
{
	if (TargetInfo->GetVisibility() != ESlateVisibility::Visible) TargetInfo->SetVisibility(ESlateVisibility::Visible);
	TargetInfo->SetInfo(Opponent);
}

void UDefaultScreenWidget::DeactivateTargetInfo()
{
	TargetInfo->SetVisibility(ESlateVisibility::Hidden);
}

void UDefaultScreenWidget::LinkStorage(class UInventorySystem* StorageInventory)
{
	Storage->LinkInventory(StorageInventory);
}

void UDefaultScreenWidget::ShowInventory()
{
	InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer()->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetOwningPlayer(), InventoryWidget);
}

void UDefaultScreenWidget::HideInventory()
{
	InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer()->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetOwningPlayer());
}

void UDefaultScreenWidget::ToggleInventory()
{
	auto InvenVisible = InventoryWidget->GetVisibility();
	switch (InvenVisible)
	{
	case ESlateVisibility::Visible:
		HideInventory();
		break;
	case ESlateVisibility::Hidden:
		ShowInventory();
		break;
	}
}

void UDefaultScreenWidget::ShowStorage()
{
	Storage->SetVisibility(ESlateVisibility::Visible);
	ShowInventory();
}

void UDefaultScreenWidget::HideStorage()
{
	Storage->SetVisibility(ESlateVisibility::Hidden);
	HideInventory();
}

void UDefaultScreenWidget::ToggleStorage()
{
	auto StorageVisible = Storage->GetVisibility();
	switch (StorageVisible)
	{
	case ESlateVisibility::Visible:
		HideStorage();
		break;
	case ESlateVisibility::Hidden:
		ShowStorage();
		break;
	}
}
