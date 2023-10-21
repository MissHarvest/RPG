// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInformationWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include "QuestGiverWidget.h"

void UQuestInformationWidget::ShowQuest(FName QuestIDToShow)
{
	FQuest Quest(QuestIDToShow);
	QuestID = QuestIDToShow;
	//auto QuestTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_QuestList.DT_QuestList'"));
	//FName QuestName = FName(*Name.ToString());
	//auto QuestInfo = QuestTable->FindRow<FQuestInfo>(QuestName, TEXT("Failed To Find Quest by Name"));

	QuestNameText->SetText(FText::FromString(Quest.GetName()));
	QuestContentText->SetText(FText::FromString(Quest.GetContent()));
	//QuestNameText->SetText(FText::FromString(QuestInfo->Name));
	//QuestContentText->SetText(FText::FromString(QuestInfo->Content));

	// Native On Init. . . ?
	AcceptButton->OnClicked.AddDynamic(this, &UQuestInformationWidget::ClickAccpetButton);
}

void UQuestInformationWidget::ClickAccpetButton()
{
	// ������ �ִ� ����Ʈ ������ ����Ʈ ���ù����� �����ؾ� �Ѵ�.
	OnAccepted.Broadcast(QuestID);
	// Quest Giver �� Quest Receiver �� �˾ƾ� �Ѵ�?
	//QuestGiverWidget->SendToGiver(QuestNameText->GetText());
	
	// Quest Giver ����Ʈ�� �˰� �־�� �Ѵ�.

	// ����Ʈ �̸��� ���� -> ���� ������
	// QuestGiverWidget->DELEGATE.BroadCast(Name);
}

void UQuestInformationWidget::SetQuestGiver(class UQuestGiverWidget* QuestGiver)
{
	QuestGiverWidget = QuestGiver;
}