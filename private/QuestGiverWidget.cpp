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
	QuestInformation->GetAcceptButton()->OnClicked.AddDynamic(this, &UQuestGiverWidget::SendToGiver);
}

void UQuestGiverWidget::AddQuest(TArray<FQuest> QuestList)
{
	if (nullptr == QuestSelectorWidgetClass) return;

	for (int i = 0; i < QuestList.Num(); ++i)
	{
		auto QuestSelector = CreateWidget<UQuestSelectorSlot>(GetWorld(), QuestSelectorWidgetClass);	
		QuestSelector->Init(QuestList[i]);
		QuestSelector->SetQuestGiver(this);
		QuestSelector->SetPadding(FMargin(0,0,0,15));
		QuestSelector->OnSelected.AddDynamic(this, &UQuestGiverWidget::ShowQuestInformation);
		QuestListBox->AddChild(QuestSelector);
	}
}

void UQuestGiverWidget::ShowQuestInformation(FQuest Quest)
{
	UE_LOG(LogTemp, Warning, TEXT("Show Quest"));
	SelectedQuest = Quest;
	QuestInformation->ShowQuest(SelectedQuest); // ������?
}

void UQuestGiverWidget::SetReceiver(class UQuestReceiver* Receiver)
{
	QuestReceiver = Receiver;
}

void UQuestGiverWidget::SendToGiver()
{
	QuestReceiver->ReceiveQuest(SelectedQuest);

	// Quest Information Clear() or Off
}