// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDragDropOperation.h"

void UItemDragDropOperation::SetOperation(class UInventorySystem* SourceInventoryToSet, int32 IndexToSet, int32 ItemID)
{
	this->SourceInventory = SourceInventoryToSet;
	this->Index = IndexToSet;
	this->ID = ItemID;
}

void UItemDragDropOperation::SetOperation(class UInventorySystem* SourceInventoryToSet, int32 IndexToSet, class UTestItem* RefItem)
{
	this->SourceInventory = SourceInventoryToSet;
	this->Index = IndexToSet;
	RefTestItem = RefItem;
}