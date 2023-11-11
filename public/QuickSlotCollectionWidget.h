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
	TArray<FString> QuickSlotKeyNameCollection;

	UPROPERTY()
	TArray<class UQuickSlotWidget*> QuickSlotWidgets;

	UPROPERTY()
	class UQuickSlotSystem* QuickSlotModel;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* QuickSlotGridBox;

protected:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION()
	void UpdateQuickSlots(int32 Index, FQuickSlot QuickSlot);

private:
	void CreateQuickSlots();

};
