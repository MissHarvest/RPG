// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomStruct.h"
#include <Engine/Texture2D.h>
#include <GameFramework/Pawn.h>
#include "ItemEffectManager.h"

// Sets default values

bool FItemSlot::Use(class APawn* OwingPawn)
{
	auto ID = Item.DataTable->FindRow<FItem>(Item.RowName, "Failed to Find ID / FItemSlot")->ID;
	auto EffectManager = OwingPawn->GetGameInstance()->GetSubsystem<UItemEffectManager>();
	return EffectManager->PrintID(ID, OwingPawn);
}

TObjectPtr<class UTexture2D> FItemSlot::GetTexture()
{
	return Item.DataTable->FindRow<FItem>(Item.RowName, "Failed to Find Texture / FItemSlot")->Texture;
}