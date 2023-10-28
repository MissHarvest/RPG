// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestGiver.h"
#include "QuestReceiver.h"

// Widget
#include "QuestGiverWidget.h"

#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

#include "MyGameInstance.h"

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
	
	auto GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		Quest = GI->GetNPCQuest(TEXT("140001"));
	}
}

void UQuestGiver::SetRecevier(class UQuestReceiver* Receiver)
{
	QuestReceiver = Receiver;
}

TArray<FQuest> UQuestGiver::GetQuestList(/* PID */)
{
	TArray<FQuest> OutArray;
	auto GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		OutArray = GI->GetNoneClearQuest(Quest, TEXT("000001"));
	}
	return OutArray;
}