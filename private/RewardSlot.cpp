// Fill out your copyright notice in the Description page of Project Settings.


#include "RewardSlot.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>

void URewardSlot::Init(FItemSlot Item)
{
	ItemImage->SetBrushFromTexture(Item.GetTexture());
	ItemQuantityText->SetText(FText::FromString(FString::FromInt(Item.GetQuantity())));
}