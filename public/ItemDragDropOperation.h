// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "CustomStruct.h"
#include "CustomEnum.h"
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

	UPROPERTY()
	ESlotType Type;

	UPROPERTY()
	int32 ID;

public:
	//void SetOperation(class UInventorySystem* SourceInventoryToSet, int32 IndexToSet, int32 ID);
	void SetOperation(class UInventorySystem* SourceInventoryToSet, int32 IndexToSet);
	int32 GetIndex() const { return Index; }
	int32 GetID() const { return ID; }
	UInventorySystem* GetSourceInventory() const { return SourceInventory; }
};
