// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInformationWidget.h"
#include <Components/TextBlock.h>

void UQuestInformationWidget::ShowQuest(FText Name)
{
	auto QuestTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/Data/DT_QuestList.DT_QuestList'"));
	FName QuestName = FName(*Name.ToString());
	auto QuestInfo = QuestTable->FindRow<FQuestInfo>(QuestName, TEXT("Failed To Find Quest by Name"));

	QuestNameText->SetText(FText::FromString(QuestInfo->Name));
	QuestContentText->SetText(FText::FromString(QuestInfo->Content));	
}