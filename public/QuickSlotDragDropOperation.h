// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "QuickSlotDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuickSlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

	UPROPERTY()
	int32 SourceIndex;

	UPROPERTY()
	class UQuickSlotSystem* QuickSlotModel;

public:
	void SetOperation(class UQuickSlotSystem* QuickSlotSystem, int32 sourceIndex);

	int32 GetIndex() const { return SourceIndex; }

	class UQuickSlotSystem* GetSystem() const { return QuickSlotModel; }
};
