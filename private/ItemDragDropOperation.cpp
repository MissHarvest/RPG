// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDragDropOperation.h"

void UItemDragDropOperation::SetOperation(class UInventorySystem* SourceInventoryToSet, int32 IndexToSet)//, int32 IDToSet)
{
	this->SourceInventory = SourceInventoryToSet;
	this->Index = IndexToSet;
	//this->ID = IDToSet;
}