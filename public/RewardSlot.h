// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomStruct.h"
#include "Blueprint/UserWidget.h"
#include "RewardSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API URewardSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemQuantityText;

public:
	/*  */
	void Init(FItemSlot Item);
};
