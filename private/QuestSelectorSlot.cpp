// Fill out your copyright notice in the Description page of Project Settings.

// Widget
#include "QuestSelectorSlot.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "QuestGiverWidget.h"

void UQuestSelectorSlot::NativeOnInitialized()
{
	Button->OnClicked.AddDynamic(this, &UQuestSelectorSlot::OnClicked);
}

void UQuestSelectorSlot::SetName(FName Name)
{
	QuestName->SetText(FText::FromName(Name));		
}

void UQuestSelectorSlot::SetQuestGiver(class UQuestGiverWidget* QuestGiver)
{
	QuestGiverWidget = QuestGiver;
}

void UQuestSelectorSlot::OnClicked()
{
	QuestGiverWidget->ShowQuestInformation(QuestName->GetText());
}