// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestReceiver.h"
#include "PlayerCharacter.h"
#include "InventorySystem.h"

// Unreal System
#include <Kismet/GameplayStatics.h>
#include "MyGameInstance.h"

// Sets default values for this component's properties
UQuestReceiver::UQuestReceiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	
}

// Called when the game starts
void UQuestReceiver::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	auto GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		PlayerQuestState = GI->GetPlayerQuestState(TEXT("000001"));
	}
}

void UQuestReceiver::AddOrUpdateQuest(FQuest Quest)
{
	switch (Quest.QuestState)
	{
	case EQuestState::Stay:
		Quest.QuestState = EQuestState::Accept;
		PlayerQuestState[Quest.GetIndex()] = EQuestState::Accept;
		Quest.Activate();
		HaveQuest.Add(Quest);		
		OnUpdatedHaveQuest.Broadcast(HaveQuest.Find(Quest), Quest);
		break;

	case EQuestState::Accept:
		PlayerQuestState[Quest.GetIndex()] = EQuestState::Stay;
		OnUpdatedHaveQuest.Broadcast(HaveQuest.Find(Quest), FQuest());
		HaveQuest.Remove(Quest);
		break;
		
	case EQuestState::CompleteStay:
		PlayerQuestState[Quest.GetIndex()] = EQuestState::Complete;
		OnUpdatedHaveQuest.Broadcast(HaveQuest.Find(Quest), FQuest());
		HaveQuest.Remove(Quest);
		// Get Reward				
		Cast<APlayerCharacter>(GetOwner())->GetInventory()->AddItem(Quest.GetReward());
		break;

	case EQuestState::Complete:
		break;
	}
}

void UQuestReceiver::UpdateQuestProgress(FName Name)
{
	for (int i = 0; i < HaveQuest.Num(); ++i)
	{
		if (HaveQuest[i].UpdateObjective(Name))
		{
			OnUpdatedHaveQuest.Broadcast(i, HaveQuest[i]);
			PlayerQuestState[HaveQuest[i].GetIndex()] = EQuestState::CompleteStay;
		}
	}
}

TArray<FQuest> UQuestReceiver::GetPerformableQuest(TArray<FString> ListQID)
{
	TArray<FQuest> PerformableQuest;
	for (int i = 0; i < ListQID.Num(); ++i)
	{
		auto Quest = FQuest(FName(*ListQID[i]));
		int32 QuestIndex = Quest.GetIndex();

		if (PlayerQuestState[QuestIndex] != EQuestState::Complete)
		{
			Quest.QuestState = PlayerQuestState[QuestIndex];
			PerformableQuest.Add(Quest);
		}		
	}
	return PerformableQuest;
}