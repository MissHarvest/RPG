// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> DT_PlayerQuestState(TEXT("/Script/Engine.DataTable'/Game/Data/DT_PlayerQuestList.DT_PlayerQuestList'"));
	if (DT_PlayerQuestState.Succeeded())
	{
		PlayerQuestStateTable = DT_PlayerQuestState.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemData(TEXT("/Script/Engine.DataTable'/Game/Data/DT_ItemList.DT_ItemList'"));
	if (DT_ItemData.Succeeded())
	{
		ItemDataTable = DT_ItemData.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> DT_NPCQuest(TEXT("/Script/Engine.DataTable'/Game/Data/DT_NPCQuestList.DT_NPCQuestList'"));
	if (DT_NPCQuest.Succeeded())
	{
		NPCQuestTable = DT_NPCQuest.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> DT_Quest(TEXT("/Script/Engine.DataTable'/Game/Data/DT_QuestList.DT_QuestList'"));
	if (DT_Quest.Succeeded())
	{
		QuestTable = DT_Quest.Object;
	}

	ConstructorHelpers::FObjectFinder<UDataTable> DT_Monster(TEXT("/Script/Engine.DataTable'/Game/Data/DT_MonsterList.DT_MonsterList'"));
	if (DT_Monster.Succeeded())
	{
		MonsterTable = DT_Monster.Object;
	}
}

TArray<EQuestState> UMyGameInstance::GetPlayerQuestState(FName PID)
{
	TArray<EQuestState> OutArray;

	if (PlayerQuestStateTable)
	{
		auto PlayerQuestState = PlayerQuestStateTable->FindRow<FPlayerQuest>(PID, TEXT(""))->Quest;
		TArray<FString> TempArray;
		PlayerQuestState.ParseIntoArray(TempArray, TEXT(","));

		for (int i = 0; i < TempArray.Num(); ++i)
		{
			OutArray.Emplace(EQuestState((uint8)FCString::Atoi(*TempArray[i])));
		}
	}
	return OutArray;
}

FItemSlot UMyGameInstance::GetItem(FName IID)
{
	if (ItemDataTable)
	{
		auto ItemData = ItemDataTable->FindRow<FItem>(IID, TEXT("Access Index Of Table/ [ item ]"));
		return FItemSlot(ItemData);
	}
	return FItemSlot();
}

TArray<FQuest> UMyGameInstance::GetNPCQuest(FName NID)
{
	TArray<FQuest> OutArray;

	if (NPCQuestTable)
	{
		auto QuestList = NPCQuestTable->FindRow<FNPCQuest>(NID, TEXT(""))->Quest;
		TArray<FString> TempArray;
		QuestList.ParseIntoArray(TempArray, TEXT(","));

		for (int i = 0; i < TempArray.Num(); ++i)
		{
			OutArray.Emplace(GetQuest(FName(*TempArray[i])));
		}
	}
	return OutArray;
}

TArray<FQuest> UMyGameInstance::GetNoneClearQuest(TArray<FQuest> NPCQuest, FName PID)
{
	TArray<FQuest> OutArray;

	auto PlayerQuestState = GetPlayerQuestState(PID);
	for (int i = 0; i < NPCQuest.Num(); ++i)
	{
		int32 QuestIndex = NPCQuest[i].GetIndex();
		if (PlayerQuestState[QuestIndex] != EQuestState::Complete)
		{
			NPCQuest[i].QuestState = PlayerQuestState[QuestIndex];
			OutArray.Emplace(NPCQuest[i]);
		}
	}
	return OutArray;
}

FQuest UMyGameInstance::GetQuest(FName QID)
{
	if (QuestTable)
	{
		auto QuestData = QuestTable->FindRow<FQuestInfo>(QID, TEXT(""));
		auto QuestRewardString = QuestData->Reward;
		auto QuestObjectiveString = QuestData->Objectives;
				
		auto QuestReward = GetItemListFromString(QuestRewardString);
		auto QuestObejctives = GetObjectivesFromString(QuestObjectiveString);
		return FQuest(QuestData, QuestReward, QuestObejctives);
	}
	return FQuest();
}

TArray<FItemSlot> UMyGameInstance::GetItemListFromString(FString String)
{
	TArray<FItemSlot> OutArray;

	TArray<FString> ItemArray;
	String.ParseIntoArray(ItemArray, TEXT(","));
	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		TArray<FString> ItemElement;
		ItemArray[i].ParseIntoArray(ItemElement, TEXT(":"));
		auto Item = GetItem(FName(*ItemElement[0]));
		Item.AddQuantity(FCString::Atoi(*ItemElement[1]));
		OutArray.Emplace(Item);
	}
	return OutArray;
}

TArray<FObjective> UMyGameInstance::GetObjectivesFromString(FString String)
{
	TArray<FObjective> OutArray;

	TArray<FString> ObjectiveArray;
	String.ParseIntoArray(ObjectiveArray, TEXT(","));
	for (int i = 0; i < ObjectiveArray.Num(); ++i)
	{
		TArray<FString> ObjectiveElement;
		ObjectiveArray[i].ParseIntoArray(ObjectiveElement, TEXT(":"));

		EObjectiveType ObjectiveType = EObjectiveType((uint8)FCString::Atoi(*ObjectiveElement[0]));

		FString TargetName;
		switch (ObjectiveType)
		{
		case EObjectiveType::Hunting:
			if (MonsterTable)
			{
				TargetName = MonsterTable->FindRow<FMonsterData>(FName(*ObjectiveElement[1]), TEXT(""))->Name;
			}
			break;

		case EObjectiveType::Deliver:
			break;

		case EObjectiveType::Collection:
			break;
		}

		int32 RequestedCount = FCString::Atoi(*ObjectiveElement[2]);

		OutArray.Emplace(FObjective(ObjectiveType, TargetName, RequestedCount));
	}
	return OutArray;
}