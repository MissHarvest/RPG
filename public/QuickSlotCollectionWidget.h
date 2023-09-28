// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotCollectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UQuickSlotCollectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UQuickSlotWidget> QuickSlotClass;

	UPROPERTY()
	TArray<class UQuickSlotWidget*> QuickSlots;

	UPROPERTY()
	class UQuickSlotSystem* QuickSlotModel;

protected:
	virtual void NativeOnInitialized() override;

public:
	void LinkQuickSlot(class UQuickSlotSystem* QuickSlot);

	void UpdateQuickSlots();

};
