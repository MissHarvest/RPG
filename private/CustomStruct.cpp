// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomStruct.h"
#include <Engine/Texture2D.h>
#include <GameFramework/Pawn.h>
#include "ItemEffectManager.h"

// Sets default values

bool FItemSlot::Use(class APawn* OwingPawn)
{
	if (0 == Quantity) return false;
	--Quantity;
	auto ID = Item.DataTable->FindRow<FItem>(Item.RowName, "Failed to Find ID / FItemSlot")->ID;
	auto EffectManager = OwingPawn->GetGameInstance()->GetSubsystem<UItemEffectManager>();
	return EffectManager->PrintID(ID, OwingPawn);
}

TObjectPtr<class UTexture2D> FItemSlot::GetTexture()
{
	return Item.DataTable->FindRow<FItem>(Item.RowName, "Failed to Find Texture / FItemSlot")->Texture;
}

TObjectPtr<class UStaticMesh> FItemSlot::GetMesh()
{
	return Item.DataTable->FindRow<FItem>(Item.RowName, "Failed to Find Mesh / FItemSlot")->Mesh;
}

int32 FItemSlot::GetID()
{
	return Item.DataTable->FindRow<FItem>(Item.RowName, "Failed to FInd Item ID / FItemSlot")->ID;
}

void FItemSlot::LinkQuickSlotIndex(int32 IndexToLink)
{
	UE_LOG(LogTemp, Warning, TEXT("Link Quick Slot Index %d"), IndexToLink);
	LinkedIndex = IndexToLink;
}

void FItemSlot::SetLinkedIndex(int32 IndexToChanage)
{
	this->LinkedIndex = IndexToChanage;
}

bool FItemSlot::IsLinked()
{
	return -1 != LinkedIndex;
}

void FItemSlot::AddQuantity(int32 CountToAdd)
{
	/* if item has max count, add condition */
	Quantity += CountToAdd;
}

bool FItemSlot::IsEmpty()
{
	return 0 == Quantity;
}

void FItemSlot::SetEmpty()
{
	Quantity = 0;
}

bool FQuickSlot::IsEmpty()
{
	return -1 == LinkedIndex;
}

void FQuickSlot::Clear()
{
	SlotType = ESlotType::None;
	ItemID = -1;
	LinkedIndex = -1;
	SourceInventory = nullptr;
}

void FQuest::Set(int32 IDofQuest)
{
	QuestManager.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_QuestList.DT_QuestList'"));
	if (QuestManager.DataTable)
	{
		auto Names = QuestManager.DataTable->GetRowNames();
		QuestManager.RowName = Names[IDofQuest];
	}
}

void FQuest::Set(FText Name)
{
	QuestManager.DataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_QuestList.DT_QuestList'"));
	if (QuestManager.DataTable)
	{
		QuestManager.RowName = FName(*Name.ToString());
	}
}

/* Operator == */
//bool operator==(const FMargin& Other) const
//{
//	return (Left == Other.Left) && (Right == Other.Right) && (Top == Other.Top) && (Bottom == Other.Bottom);
//}

FString FQuest::GetName() const
{
	return QuestManager.DataTable->FindRow<FQuestInfo>(QuestManager.RowName, TEXT("Failed"))->Name;
}

FName FQuest::GetID()
{
	return QuestManager.RowName;
}

FString FQuest::GetContent()
{
	return QuestManager.DataTable->FindRow<FQuestInfo>(QuestManager.RowName, TEXT("Failed"))->Content;
}

FString FQuest::GetSummary()
{
	return QuestManager.DataTable->FindRow<FQuestInfo>(QuestManager.RowName, TEXT("Failed"))->Summary;
}

TArray<FObjective> FQuest::GetObjectives()
{
	return Objectives;
}

void FQuest::Activate()
{
	auto Quest = QuestManager.DataTable->FindRow<FQuestInfo>(QuestManager.RowName, TEXT("Failed"));
	
	FString Data = Quest->Objectives;
	TArray<FString> temp;
	Data.ParseIntoArray(temp, TEXT(","));

	EObjectiveType ObjectiveType = (EObjectiveType)(FCString::Atoi(*temp[0]));
	FString ObjectiveName = temp[1];
	int32 ObjectiveCount = FCString::Atoi(*temp[2]);

	FObjective Objective(ObjectiveType, Quest->Summary, ObjectiveName, ObjectiveCount);
	Objectives.Emplace(Objective);
}

void FQuest::UpdateObjective(FName Name)
{
	for (int i = 0; i < Objectives.Num(); ++i)
	{
		if (Objectives[i].IsTarget(Name))
		{
			Objectives[i].ProgressCount += 1;
		}
	}
}

bool FObjective::IsTarget(FName Name)
{
	return MID == Name;
}
