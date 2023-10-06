// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

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
		if (bIsEmpty) return UWidgetBlueprintLibrary::Unhandled().NativeReply;
		InventoryModel->ConsumeItemByIndex(MyIndex);
	}
	return UWidgetBlueprintLibrary::Unhandled().NativeReply;	
}

void UItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	// 원본 코드 /
	if (bIsEmpty) return;

	auto Preview = CreateWidget<UDragItemPreviewWidget>(GetOwningPlayer(), DragItemPreviewClass);
	Preview->SetThumbnail(ThumbnailTexture);
	auto DragDrop = UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass);	
	DragDrop->DefaultDragVisual = Preview;
	Cast<UItemDragDropOperation>(DragDrop)->SetOperation(InventoryModel, MyIndex, 0); //ItemModel.GetID()
	UE_LOG(LogTemp, Warning, TEXT("Drag %d Index Item"), MyIndex);
	OutOperation = DragDrop;
}

bool UItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto Operation = Cast<UItemDragDropOperation>(InOperation);
	if (IsValid(Operation))
	{
		InventoryModel->SwapItem(Operation->GetSourceInventory(), Operation->GetIndex(), MyIndex);
		UE_LOG(LogTemp, Warning, TEXT("%d -> %d"), Operation->GetIndex(), MyIndex);
	}

	// InventoryWidget.Changed --> InventoryWidget.BroadCast To Inventory
	return false;
}

void UItemSlotWidget::SetItem(FItemSlot ItemSlot)
{
	if (ItemSlot.IsEmpty())
	{
		bIsEmpty = true;
		ThumbnailTexture = nullptr;
		Thumbnail->SetBrushFromTexture(ThumbnailTexture);
		Quantity->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		bIsEmpty = false;
		ThumbnailTexture = ItemSlot.GetTexture();
		Quantity->SetVisibility(ESlateVisibility::Visible);
		Quantity->SetText(
			FText::FromString(
				FString::FromInt(ItemSlot.GetQuantity())
			)
		);
		Thumbnail->SetBrushFromTexture(ThumbnailTexture);
	}
}

void UItemSlotWidget::SetInventoryModel(class UInventorySystem* TargetInventory)
{
	InventoryModel = TargetInventory;
}

void UItemSlotWidget::SetIndex(int32 IndexToSet)
{
	this->MyIndex = IndexToSet;
}