// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "CustomStruct.h"
#include "ItemDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
	UPROPERTY()
	class UInventorySystem* SourceInventory;

	UPROPERTY()
	int32 Index;

public:
	void SetOperation(class UInventorySystem* SourceInventoryToSet, int32 IndexToSet);
	int32 GetIndex() const { return Index; }
};
