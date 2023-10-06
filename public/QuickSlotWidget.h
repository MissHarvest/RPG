// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomStruct.h"
#include "CustomEnum.h"
#include "QuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 ID;

	UPROPERTY()
	int32 MyIndex;

	UPROPERTY()
	class UQuickSlotSystem* QuickSlotModel;

	UPROPERTY()
	ESlotType SlotType;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Thumbnail;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* KeyName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Quantity;

public:
	void SetQuickSlot(FQuickSlot QuickSlot);
	void SetQuickSlotModel(class UQuickSlotSystem* QuickSlot);
	void SetIndex(int32 IndexToSet);
	void SetKeyName(FString KeyNameToSet);

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
