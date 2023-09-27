// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include <Components/Image.h>

// Other
#include "CustomStruct.h"
#include <Engine/Texture2D.h>
#include "InventorySystem.h"

// Source
#include "ItemDragDropOperation.h"
#include "DragItemPreviewWidget.h"

// System
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Input/Reply.h>

FReply UItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Slot Pressed"));
		auto ReturnValue = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return ReturnValue.NativeReply;
	}
	
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		InventoryModel->ConsumeItem(Index);
	}
	return UWidgetBlueprintLibrary::Unhandled().NativeReply;	
}

void UItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (ItemModel.Item.IsNull()) return;

	// Create Drag Widget
	auto Preview = CreateWidget<UDragItemPreviewWidget>(GetOwningPlayer(), DragItemPreviewClass);
	
	// Set Thumbnail in Drag Widget
	auto Texture = ItemModel.GetTexture();
	Preview->SetThumbnail(Texture);

	// Create Operation
	auto DragDrop = UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass);	
	DragDrop->DefaultDragVisual = Preview;

	// Set Operation
	Cast<UItemDragDropOperation>(DragDrop)->SetOperation(InventoryModel, Index);
	OutOperation = DragDrop;
}

bool UItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto Operation = Cast<UItemDragDropOperation>(InOperation);
	if (IsValid(Operation))
	{
		InventoryModel->SwapItem(Operation->GetSourceInventory(), Operation->GetIndex(), Index);
		UE_LOG(LogTemp, Warning, TEXT("%d -> %d"), Operation->GetIndex(), Index);
	}
	return false;
}

void UItemSlotWidget::SetItem(FItemSlot ItemSlot)
{
	if (ItemSlot.Item.IsNull())
	{
		ItemModel = FItemSlot::FItemSlot();
		Thumbnail->SetBrushFromTexture(nullptr);		
	}
	else
	{
		ItemModel = ItemSlot;
		auto ItemTexture = ItemModel.GetTexture();
		Thumbnail->SetBrushFromTexture(ItemTexture);
	}
}

void UItemSlotWidget::SetInventoryModel(class UInventorySystem* TargetInventory)
{
	InventoryModel = TargetInventory;
}

void UItemSlotWidget::SetIndex(int32 IndexToSet)
{
	this->Index = IndexToSet;
}