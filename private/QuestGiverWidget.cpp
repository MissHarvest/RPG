// Fill out your copyright notice in the Description page of Project Settings.

// Widget
#include "QuestGiverWidget.h"
#include <Components/VerticalBox.h>
#include "QuestInformationWidget.h"
#include "QuestSelectorSlot.h"

void UQuestGiverWidget::AddQuest(TArray<FQuest> QuestList)
{
	if (nullptr == QuestSelectorWidgetClass) return;

	for (int i = 0; i < QuestList.Num(); ++i)
	{
		auto QuestSelector = CreateWidget<UQuestSelectorSlot>(GetWorld(), QuestSelectorWidgetClass);		
		QuestSelector->SetName(QuestList[i].GetName());
		QuestSelector->SetQuestGiver(this);
		FMargin Margin;
		Margin.Bottom = 15.0f;
		QuestSelector->SetPadding(Margin);
		QuestSelectors.Add(QuestSelector);
		QuestListBox->AddChild(QuestSelector);
	}
}

void UQuestGiverWidget::ShowQuestInformation(FText QuestName)
{
	QuestInformation->ShowQuest(QuestName);
}
