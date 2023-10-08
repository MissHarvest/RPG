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
#include "InventorySystem.h"
#include <Components/TextBlock.h>
#include "QuickSlotDragDropOperation.h"
#include "DragItemPreviewWidget.h"

FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		UE_LOG(LogTemp, Warning, TEXT("Quick Slot Pressed"));
		auto ReturnValue = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return ReturnValue.NativeReply;
	}

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		// Slot ºñ¿ì±â 
	}
	return UWidgetBlueprintLibrary::Unhandled().NativeReply;
}

void UQuickSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (IsEmpty()) return;

	auto Preview = CreateWidget<UDragItemPreviewWidget>(GetOwningPlayer(), DragItemPreviewClass);
	Preview->SetThumbnail(ThumbnailTexture);

	auto DragDrop = UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass);
	DragDrop->DefaultDragVisual = Preview;
	Cast<UQuickSlotDragDropOperation>(DragDrop)->SetOperation(MyIndex); 
	OutOperation = DragDrop;
}

bool UQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto ItemOperation = Cast<UItemDragDropOperation>(InOperation);	
	if (ItemOperation)
	{
		auto SourceInventory = ItemOperation->GetSourceInventory();
		auto SourceIndex = ItemOperation->GetIndex();
		auto ItemID = ItemOperation->GetID();

		if (nullptr == QuickSlotModel) return false;
		SourceInventory->GetContent(SourceIndex).LinkQuickSlotIndex(MyIndex);
		QuickSlotModel->UpdateQuickSlotInfoByIndex(MyIndex, SourceInventory, SourceIndex);
		return true;
	}

	auto QuickOperation = Cast<UQuickSlotDragDropOperation>(InOperation);
	if(QuickOperation)
	{
		QuickSlotModel->SwapQuickSlot(QuickOperation->GetIndex(), MyIndex);
		return true;
	}
	return false;
	
}

void UQuickSlotWidget::SetQuickSlot(FQuickSlot QuickSlot)
{
	switch (QuickSlot.SlotType)
	{
	case ESlotType::None:
		Thumbnail->SetBrushFromTexture(nullptr);
		Quantity->SetText(FText::FromString(FString::FromInt(0)));
		Quantity->SetVisibility(ESlateVisibility::Hidden);
		break;

	case ESlotType::Item:
		if(QuickSlot.SourceInventory->GetContent(QuickSlot.LinkedIndex).IsEmpty() == false)
			ThumbnailTexture = QuickSlot.SourceInventory->GetContent(QuickSlot.LinkedIndex).GetTexture();
		Thumbnail->SetBrushFromTexture(ThumbnailTexture);
		Quantity->SetText(FText::FromString(FString::FromInt(QuickSlot.SourceInventory->GetContent(QuickSlot.LinkedIndex).GetQuantity())));
		Quantity->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESlotType::Skill:

		break;

	default:

		break;
	}
}

void UQuickSlotWidget::SetQuickSlotModel(class UQuickSlotSystem* QuickSlot)
{
	QuickSlotModel = QuickSlot;
}

void UQuickSlotWidget::SetIndex(int32 IndexToSet)
{
	MyIndex = IndexToSet;
}

void UQuickSlotWidget::SetKeyName(FString KeyNameToSet)
{
	KeyName->SetText(FText::FromString(KeyNameToSet));
}
