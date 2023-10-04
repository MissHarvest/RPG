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
		// 원본 코드 //
		if (ItemModel.Item.IsNull()) return UWidgetBlueprintLibrary::Unhandled().NativeReply;
		InventoryModel->ConsumeItem(ItemModel.GetID());

		/*if (nullptr == TestItemModel) return UWidgetBlueprintLibrary::Unhandled().NativeReply;
		UE_LOG(LogTemp, Warning, TEXT("%d Slot iss not nullptr"), Index);
		InventoryModel->ConsumeItem(Index);*/
	}
	return UWidgetBlueprintLibrary::Unhandled().NativeReply;	
}

void UItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	// 원본 코드 /
	if (ItemModel.Item.IsNull()) return;

	auto Preview = CreateWidget<UDragItemPreviewWidget>(GetOwningPlayer(), DragItemPreviewClass);
	auto Texture = ItemModel.GetTexture();
	Preview->SetThumbnail(Texture);
	auto DragDrop = UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass);	
	DragDrop->DefaultDragVisual = Preview;
	Cast<UItemDragDropOperation>(DragDrop)->SetOperation(InventoryModel, Index, ItemModel.GetID()); 
	UE_LOG(LogTemp, Warning, TEXT("Drag %d Index Item"), Index);
	OutOperation = DragDrop;

	/* Test Code /
	if (nullptr == TestItemModel) return;
	auto Preview = CreateWidget<UDragItemPreviewWidget>(GetOwningPlayer(), DragItemPreviewClass);
	auto Texture = TestItemModel->GetTexture();
	Preview->SetThumbnail(Texture);
	auto DragDrop = UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass);
	DragDrop->DefaultDragVisual = Preview;
	Cast<UItemDragDropOperation>(DragDrop)->SetOperation(InventoryModel, Index, TestItemModel);
	UE_LOG(LogTemp, Warning, TEXT("Drag %d Index Item"), Index);
	OutOperation = DragDrop;
	*/
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
		Quantity->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ItemModel = ItemSlot;
		auto ItemTexture = ItemModel.GetTexture();
		Quantity->SetVisibility(ESlateVisibility::Visible);
		Quantity->SetText(FText::FromString(FString::FromInt(ItemModel.Quentity)));
		Thumbnail->SetBrushFromTexture(ItemTexture);
	}
}

void UItemSlotWidget::SetItem(class UTestItem* RefItem)
{
	if (nullptr == RefItem)
	{
		ItemModel = FItemSlot::FItemSlot();
		Thumbnail->SetBrushFromTexture(nullptr);
		Quantity->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TestItemModel = RefItem;
		auto ItemTexture = RefItem->GetTexture();//ItemModel.GetTexture();
		Quantity->SetVisibility(ESlateVisibility::Visible);
		Quantity->SetText(FText::FromString(FString::FromInt(RefItem->Quentity)));
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