// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomStruct.h"
#include "ItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
	class UInventorySystem* InventoryModel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget, AllowPrivateAccess = "true"))
	class UImage* Thumbnail;

	UPROPERTY()
	FItemSlot ItemModel;

	UPROPERTY()
	int32 Index;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Source", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDragItemPreviewWidget> DragItemPreviewClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Source", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemDragDropOperation> DragDropOperationClass;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

public:
	void SetItem(FItemSlot ItemSlot);
	void SetInventoryModel(class UInventorySystem* TargetInventory);
	void SetIndex(int32 IndexToSet);
};
