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
	//QuickSlotModel->SetQuickSlot(SlotIndex, SourceInventory, SourceIndex);
	UE_LOG(LogTemp, Warning, TEXT("Drop Quick Slot Item ID : %d / Slot Index : %d"), ItemID, SlotIndex);
	QuickSlotModel->SetQuickSlot(SlotIndex, SourceInventory, ItemID);
	return true;

	/* Test Code /
	if (nullptr == QuickSlotModel) return false;
	QuickSlotModel->SetQuickSlot(SlotIndex, Operation->RefTestItem);
	return true;
	*/
}

void UQuickSlotWidget::SetQuickSlot(FQuickSlot QuickSlot)
{
	// if (-1 == QuickSlot.Index) return; // QuickSlot Struct Empty check Function Add

	if (0 == QuickSlot.ItemID) return;

	if (ESlotType::Item == QuickSlot.SlotType) // enum not include
	{
		auto Inven = QuickSlot.SourceInventory;
		auto Index = QuickSlot.Index;
		auto Ref_ID = QuickSlot.ItemID;

		if (-1 != Inven->GetItem(Ref_ID))//.Item.IsNull() == false)
		{
			auto Texture = Inven->GetContent(Inven->GetItem(Ref_ID)).GetTexture();
			Thumbnail->SetBrushFromTexture(Texture);
			Quantity->SetText(FText::FromString(FString::FromInt(Inven->GetContent(Inven->GetItem(Ref_ID)).Quentity)));
			Quantity->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Quantity->SetText(FText::FromString(FString::FromInt(0)));
			Quantity->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UQuickSlotWidget::SetQuickSlot(class UTestItem* RefItem)
{
	if (nullptr == RefItem) return;

	Thumbnail->SetBrushFromTexture(RefItem->GetTexture());
	Quantity->SetText(FText::FromString(FString::FromInt(RefItem->Quentity)));
	Quantity->SetVisibility(ESlateVisibility::Visible);
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
