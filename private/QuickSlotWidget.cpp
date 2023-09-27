// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "ItemDragDropOperation.h"
#include "InventorySystem.h"
#include "CustomStruct.h"
#include <Engine/Texture2D.h>
#include <Components/Image.h>
#include "QuickSlotSystem.h"
#include <Components/TextBlock.h>

FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::Unhandled().NativeReply;
}

void UQuickSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{

}

bool UQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto Operation = Cast<UItemDragDropOperation>(InOperation);
	if (nullptr == Operation) return false;
	if (nullptr == QuickSlotModel) return false;

	// Type, Model, Index
	QuickSlotModel->SetQuickSlot(Operation->GetSourceInventory(), Operation->GetIndex(), SlotIndex);
	return true;
}

void UQuickSlotWidget::SetQuickSlot(FQuickSlot QuickSlot)
{
	// ID = QuickSlot.ID;
	KeyName->SetText(FText::FromString(FString::FromInt(QuickSlot.Index)));

	//if (QuickSlot.SourceInventory->GetContent(QuickSlot.Index).Item.IsNull())
	//{
	//	// if item count == 0 
	//	// SourceInventory == nullptr
	//}
}

void UQuickSlotWidget::SetQuickSlotModel(class UQuickSlotSystem* QuickSlot)
{
	QuickSlotModel = QuickSlot;
}

void UQuickSlotWidget::SetIndex(int32 IndexToSet)
{
	SlotIndex = IndexToSet;
}