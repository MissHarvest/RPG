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

	UPROPERTY()
	int32 MyIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Source", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDragItemPreviewWidget> DragItemPreviewClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Source", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemDragDropOperation> DragDropOperationClass;

	UPROPERTY()
	TObjectPtr<class UTexture2D> ThumbnailTexture;

	UPROPERTY()
	bool bIsEmpty;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Thumbnail;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Quantity;

protected:
	/*  */
	virtual void NativeOnInitialized() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

public:
	void SetItem(FItemSlot ItemSlot);
	void SetInventoryModel(class UInventorySystem* TargetInventory);
	void SetIndex(int32 IndexToSet);
};
