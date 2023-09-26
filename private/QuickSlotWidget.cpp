// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "ItemDragDropOperation.h"
#include "InventorySystem.h"
#include "CustomStruct.h"
#include <Engine/Texture2D.h>
#include <Components/Image.h>

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

	// Target Quick Slot System need . . .
	// TargetQuickSlot->UpdateQuickSlot();
	
	// 

	//Operation->GetSourceInventory()->GetContent(Operation->GetIndex()).Item.DataTable->FindRow<FItem>()
	//this->ID = Operation->GetID();
	//auto ItemModel = Operation->GetSourceInventory()->GetContent(Operation->GetIndex());
	//auto Texture = ItemModel.Item.DataTable->FindRow<FItem>(ItemModel.Item.RowName, "Failed")->Texture;
	//Thumbnail->SetBrushFromTexture(Texture);
	return true;
}

void UQuickSlotWidget::SetQuickSlot(FQuickSlot QuickSlot)
{

}

void UQuickSlotWidget::SetQuickSlotModel(class UQuickSlotSystem* QuickSlot)
{

}