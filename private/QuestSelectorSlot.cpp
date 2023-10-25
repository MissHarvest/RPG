// Fill out your copyright notice in the Description page of Project Settings.

// Widget
#include "QuestSelectorSlot.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "QuestGiverWidget.h"

void UQuestSelectorSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Button->OnClicked.AddDynamic(this, &UQuestSelectorSlot::OnClicked);
}

void UQuestSelectorSlot::Init(int32 IndexOfList, FString QuestName)
{
	Index = IndexOfList;
	QuestNameText->SetText(FText::FromString(QuestName));
}

void UQuestSelectorSlot::SetQuestGiver(class UQuestGiverWidget* QuestGiver)
{
	QuestGiverWidget = QuestGiver;
}

void UQuestSelectorSlot::OnClicked()
{
	QuestGiverWidget->ShowQuestInformation(Index);
}