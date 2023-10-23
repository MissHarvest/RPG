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

	// Load Quest Id List

	QuestIdList.Add(1);
	QuestIdList.Add(2);
	QuestIdList.Add(3);
	
	for (int i = 0; i < QuestIdList.Num(); ++i)
	{
		FQuest Quest;
		Quest.Set(QuestIdList[i]);
		QuestList.Add(Quest);
	}
}


// Called when the game starts
void UQuestGiver::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("Giver Begin"));
	// ...
	
}

void UQuestGiver::ShowQuestPanel()
{
	if (nullptr == QuestPanelWidgetClass) return;
	
	QuestGiverWidget = CreateWidget<UQuestGiverWidget>(GetWorld(), QuestPanelWidgetClass);
	if (QuestGiverWidget)
	{
		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, QuestGiverWidget);
		QuestGiverWidget->SetModel(this);
		QuestGiverWidget->AddQuest(QuestList); // quest id list ? 
		QuestGiverWidget->AddToViewport();
	}
}

void UQuestGiver::GiveQuestToReceiver(FName QuestID)
{
	FQuest Quest(QuestID);	
	QuestReceiver->ReceiveQuest(Quest);	
}

void UQuestGiver::SetRecevier(class UQuestReceiver* Receiver)
{
	QuestReceiver = Receiver;
}

void UQuestGiver::CloseQuestGiverWidget()
{
	if (QuestGiverWidget)
	{
		QuestGiverWidget->RemoveFromParent();
		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	}
}
