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

	auto SourceInventory = Operation->GetSourceInventory();
	auto SourceIndex = Operation->GetIndex();

	if (nullptr == QuickSlotModel) return false;
	QuickSlotModel->SetQuickSlot(SlotIndex, SourceInventory, SourceIndex);
	return true;
}

void UQuickSlotWidget::SetQuickSlot(FQuickSlot QuickSlot)
{
	if (-1 == QuickSlot.Index) return; // QuickSlot Struct Empty check Function Add

	if (ESlotType::Item == QuickSlot.SlotType) // enum not include
	{
		auto Inven = QuickSlot.SourceInventory;
		auto Index = QuickSlot.Index;
		auto Texture = Inven->GetContent(Index).GetTexture();
		Thumbnail->SetBrushFromTexture(Texture);
	}
}

void UQuickSlotWidget::SetQuickSlotModel(class UQuickSlotSystem* QuickSlot)
{
	QuickSlotModel = QuickSlot;
}

void UQuickSlotWidget::SetIndex(int32 IndexToSet)
{
	SlotIndex = IndexToSet;
}

void UQuickSlotWidget::SetKeyName(FString KeyNameToSet)
{
	KeyName->SetText(FText::FromString(KeyNameToSet));
}
