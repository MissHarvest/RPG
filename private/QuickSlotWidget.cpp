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

	//* 원본 코드 /
	auto SourceInventory = Operation->GetSourceInventory();
	auto SourceIndex = Operation->GetIndex();
	auto ItemID = Operation->GetID();

	if (nullptr == QuickSlotModel) return false;
	SourceInventory->GetContent(SourceIndex).LinkQuickSlotIndex(MyIndex);
	QuickSlotModel->UpdateQuickSlotInfoByIndex(MyIndex, SourceInventory, SourceIndex);
	return true;
}

void UQuickSlotWidget::SetQuickSlot(FQuickSlot QuickSlot)
{
	/* IsLinked? */
	if (false == QuickSlot.IsSet()) return;

	if (ESlotType::Item == QuickSlot.SlotType)
	{
		auto Inven = QuickSlot.SourceInventory;
		auto Index = QuickSlot.LinkedIndex;
		
		if (Inven->GetItemByIndex(Index).IsEmpty())
		{
			Quantity->SetText(FText::FromString(FString::FromInt(0)));
			Quantity->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			auto Texture = Inven->GetContent(Index).GetTexture();
			Thumbnail->SetBrushFromTexture(Texture);
			Quantity->SetText(FText::FromString(FString::FromInt(Inven->GetContent(Index).GetQuantity())));
			Quantity->SetVisibility(ESlateVisibility::Visible);
		}
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
