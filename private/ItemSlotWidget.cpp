// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "CustomStruct.h"
#include <Components/Image.h>

#include <Engine/Texture2D.h>

#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Input/Reply.h>

//FReply UItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	
//	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//
//	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Item Slot Pressed"));
//		auto ReturnValue = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
//		return ReturnValue.NativeReply;
//	}
//	
//	return UWidgetBlueprintLibrary::Unhandled().NativeReply;	
//}


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
		auto ItemTexture = ItemModel.Item.DataTable->FindRow<FItem>(ItemSlot.Item.RowName, "Failed")->Texture;
		Thumbnail->SetBrushFromTexture(ItemTexture);
	}
}