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

	UPROPERTY()
	int32 ID;

public:
	void SetQuickSlot(FQuickSlot QuickSlot);
	void SetQuickSlotModel(class UQuickSlotSystem* QuickSlot);

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
