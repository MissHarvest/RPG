// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSlot.h"
#include <Components/TextBlock.h>
#include "ObjectiveSlot.h"
#include <Components/VerticalBox.h>

void UQuestSlot::SetQuest(FQuest Quest)
{
	QuestNameText->SetText(FText::FromString(Quest.GetName()));
	
	FString Data = Quest.GetObjectives();
	TArray<FString> temp;
	Data.ParseIntoArray(temp, TEXT(","));
	EObjectiveType ObjectiveType = (EObjectiveType)(FCString::Atoi(*temp[0]));
	FString Summary = temp[1];
	int32 ObjectiveCount = FCString::Atoi(*temp[2]);
	FObjective Objective(ObjectiveType, Summary, ObjectiveCount);

	AddObjective(Objective); 	
}

void UQuestSlot::AddObjective(FObjective Objective)
{
	if (ObjectiveSlotClass)
	{
		auto ObjectiveSlot = CreateWidget<UObjectiveSlot>(GetOwningPlayer(), ObjectiveSlotClass);
		ObjectiveSlot->SetObjective(Objective);
		ObjectiveListBox->AddChild(ObjectiveSlot);
	}
}