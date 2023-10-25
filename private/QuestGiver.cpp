// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestGiver.h"
#include "QuestReceiver.h"

// Widget
#include "QuestGiverWidget.h"

#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>


// Sets default values for this component's properties
UQuestGiver::UQuestGiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//UE_LOG(LogTemp, Warning, TEXT("Giver Constructor"));

}


// Called when the game starts
void UQuestGiver::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("Giver Begin"));
	// ...
	
}

void UQuestGiver::SetRecevier(class UQuestReceiver* Receiver)
{
	QuestReceiver = Receiver;
}

void UQuestGiver::LoadTable(const TCHAR* Path, FName NID)
{
	NPCQuestTable = LoadObject<UDataTable>(NULL, Path);
	if (NPCQuestTable)
	{
		auto QuestStr = NPCQuestTable->FindRow<FNPCQuest>(NID, TEXT("Failed"))->Quest;
		QuestStr.ParseIntoArray(ListQID, TEXT(","));
	}
}