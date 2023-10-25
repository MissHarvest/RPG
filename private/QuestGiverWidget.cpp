// Fill out your copyright notice in the Description page of Project Settings.

// Widget
#include "QuestGiverWidget.h"
#include <Components/VerticalBox.h>
#include "QuestInformationWidget.h"
#include "QuestSelectorSlot.h"
#include <Components/Button.h>

//
#include "QuestGiver.h"
#include "QuestReceiver.h"

void UQuestGiverWidget::NativeOnInitialized()
{
	QuestInformation->SetQuestGiver(this);
	//QuestInformation->GetAcceptButton()->OnClicked.AddDynamic(this, &UQuestGiverWidget::SendToGiver);
}

void UQuestGiverWidget::AddQuest(TArray<FQuest> QuestList)
{
	if (nullptr == QuestSelectorWidgetClass) return;
	PerformableQuest = QuestList;

	for (int i = 0; i < QuestList.Num(); ++i)
	{
		auto QuestSelector = CreateWidget<UQuestSelectorSlot>(GetWorld(), QuestSelectorWidgetClass);	
		QuestSelector->Init(i, PerformableQuest[i].GetName());
		QuestSelector->SetQuestGiver(this);
		QuestSelector->SetPadding(FMargin(0,0,0,15));
		QuestListBox->AddChild(QuestSelector);
	}
}

void UQuestGiverWidget::ShowQuestInformation(int32 IndexOfList)
{
	SelectedIndex = IndexOfList;
	QuestInformation->ShowQuest(PerformableQuest[SelectedIndex]);
}

void UQuestGiverWidget::SetReceiver(class UQuestReceiver* Receiver)
{
	QuestReceiver = Receiver;
}

/* 함수 이름 변경 */
void UQuestGiverWidget::SendToGiver()
{
	QuestReceiver->AddOrUpdateQuest(PerformableQuest[SelectedIndex]);
	
	switch (PerformableQuest[SelectedIndex].QuestState)
	{
	case EQuestState::Stay:
		PerformableQuest[SelectedIndex].QuestState = EQuestState::Accept;
		break;

	case EQuestState::Accept:
		PerformableQuest[SelectedIndex].QuestState = EQuestState::Stay;
		break;

	case EQuestState::CompleteStay:
		//PerformableQuest[SelectedIndex].QuestState = EQuestState::Complete;
		QuestListBox->RemoveChildAt(SelectedIndex);
		break;

	case EQuestState::Complete:
		break;
	}
		
	//QuestInformation->ShowQuest(PerformableQuest[SelectedIndex]);
	// QuestInformation. Reset()
}