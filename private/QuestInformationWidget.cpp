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
	// 가지고 있는 퀘스트 정보를 퀘스트 리시버에게 전달해야 한다.
	OnAccepted.Broadcast(QuestID);
	// Quest Giver 은 Quest Receiver 를 알아야 한다?
	//QuestGiverWidget->SendToGiver(QuestNameText->GetText());
	
	// Quest Giver 포인트를 알고 있어야 한다.

	// 퀘스트 이름을 전달 -> 상위 위젯에
	// QuestGiverWidget->DELEGATE.BroadCast(Name);
}

void UQuestInformationWidget::SetQuestGiver(class UQuestGiverWidget* QuestGiver)
{
	QuestGiverWidget = QuestGiver;
}