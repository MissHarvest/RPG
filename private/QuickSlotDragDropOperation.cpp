// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotDragDropOperation.h"

void UQuickSlotDragDropOperation::SetOperation(class UQuickSlotSystem* QuickSlotSystem,int32 sourceIndex)
{
	SourceIndex = sourceIndex;
	QuickSlotModel = QuickSlotSystem;
}