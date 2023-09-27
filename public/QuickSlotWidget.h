// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomStruct.h"
#include "QuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget, AllowPrivateAccess = "true"))
	class UImage* Thumbnail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget, AllowPrivateAccess = "true"))
	class UTextBlock* KeyName;

	UPROPERTY()
	int32 ID;

	UPROPERTY()
	int32 SlotIndex;

	UPROPERTY()
	class UQuickSlotSystem* QuickSlotModel;

public:
	void SetQuickSlot(FQuickSlot QuickSlot);
	void SetQuickSlotModel(class UQuickSlotSystem* QuickSlot);
	void SetIndex(int32 IndexToSet);

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
