// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDragDropOperation.h"
#include "CustomEnum.h"

void UItemDragDropOperation::SetOperation(class UInventorySystem* SourceInventoryToSet, int32 IndexToSet)
{
	this->SourceInventory = SourceInventoryToSet;
	this->Index = IndexToSet;
	//this->ID = IDToSet;
	Type = ESlotType::Item;
}