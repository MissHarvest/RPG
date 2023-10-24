// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInformationWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "QuestGiverWidget.h"

void UQuestInformationWidget::ShowQuest(FQuest Quest)//FQuest 로 바꿔야할듯
{
	QuestNameText->SetText(FText::FromString(Quest.GetName()));
	QuestContentText->SetText(FText::FromString(Quest.GetContent()));

	FString Label;// = TEXT("수락");
	switch (Quest.QuestState)
	{
	case EQuestState::Stay:
		Label = TEXT("수락");
		break;
	case EQuestState::Accept:
		Label = TEXT("포기");
		break;
	}
	ButtonText->SetText(FText::FromString(Label));
}

void UQuestInformationWidget::SetQuestGiver(class UQuestGiverWidget* QuestGiver)
{
	QuestGiverWidget = QuestGiver;
}