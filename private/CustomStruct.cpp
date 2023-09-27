// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomStruct.h"
#include <Engine/Texture2D.h>
#include <GameFramework/Pawn.h>
#include "ItemEffectManager.h"

// Sets default values

bool FItem::UseItem(class APawn* OwingPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Use"));
	auto EffectManager = OwingPawn->GetGameInstance()->GetSubsystem<UItemEffectManager>();
	return EffectManager->PrintID(ID, OwingPawn);
}


TObjectPtr<class UTexture2D> FItemSlot::GetTexture()
{
	if (Item.IsNull()) return nullptr;

	// GetRow()
	return Item.DataTable->FindRow<FItem>(Item.RowName, "Failed To Find Item/Texture")->Texture;
	//return nullptr;
}