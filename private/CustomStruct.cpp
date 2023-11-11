// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomStruct.h"
#include <Engine/Texture2D.h>
#include <GameFramework/Pawn.h>
#include "ItemEffectManager.h"

// Sets default values

TObjectPtr<class UTexture2D> FItemSlot::GetTexture()
{
	return Item.Texture;
}

FName FItemSlot::GetID()
{
	return IID;
}

FString FItemSlot::GetName() const
{
	return Item.Name;
}

void FItemSlot::AddQuantity(int32 CountToAdd)
{
	/* if item has max count, add condition */
	Quantity += CountToAdd;
}

bool FItemSlot::Consume(int32 CountToUse)
{
	if (0 == Quantity) return false;
	Quantity -= CountToUse;
	return true;
}

bool FItemSlot::IsEmpty()
{
	return 0 == Quantity;
}

void FItemSlot::SetEmpty()
{
	Quantity = 0;
}

//
// FQuickSlot
//
bool FQuickSlot::IsEmpty()
{
	return -1 == LinkedIndex;
}

void FQuickSlot::Clear()
{
	SlotType = ESlotType::None;
	LinkedIndex = -1;
	SourceInventory = nullptr;
}

FString FQuickSlot::GetName()
{
	return Name;
}

FString FQuest::GetName() const
{
	return Quest.Name;
}

int32 FQuest::GetIndex()
{
	return Quest.Index;
}

FString FQuest::GetContent()
{
	return Quest.Content;
}

FString FQuest::GetSummary()
{
	return Quest.Summary;
}

TArray<FObjective> FQuest::GetObjectives()
{
	return Objectives;
}

TArray<FItemSlot> FQuest::GetReward()
{
	return Rewards;
}

bool FQuest::UpdateObjective(FName Name)
{
	bool bUpdated = false;
	for (int i = 0; i < Objectives.Num(); ++i)
	{
		if (Objectives[i].IsTarget(Name))
		{
			bUpdated = true;
			Objectives[i].ProgressCount += 1;
			if (Objectives[i].ProgressCount == Objectives[i].RequestedCount)
			{
				Objectives[i].bCompleted = true;
			}
		}
	}
	if (bUpdated == false) return bUpdated;

	bool bIsCompleted = true;
	for (int i = 0; i < Objectives.Num(); ++i)
	{
		bIsCompleted = bIsCompleted && Objectives[i].bCompleted;		
	}
	if (bIsCompleted)
	{
		QuestState = EQuestState::CompleteStay;
	}
	return bUpdated;
}

bool FObjective::IsTarget(FName Name)
{
	return FName(*Target) == Name;
}
