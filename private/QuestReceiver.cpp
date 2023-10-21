// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestReceiver.h"

// Sets default values for this component's properties
UQuestReceiver::UQuestReceiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestReceiver::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestReceiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestReceiver::ReceiveQuest(FQuest ReceivedQuest)
{
	//HaveQuest = Quest;
	HaveQuest.Add(ReceivedQuest);
	int32 index_ = HaveQuest.IndexOfByPredicate([=](const FQuest& Quest) { return Quest.GetName() == ReceivedQuest.GetName(); });
	OnQuestUpdated.Broadcast(index_, ReceivedQuest);
}